#include <QBrush>
#include <QDateTime>
#include <QFile>
#include <QFont>
#include <QIcon>
#include <array>

#include "qspdlog_model.hpp"

namespace
{

QStringList icon_names = (QStringList() << ":/res/trace.png" << ":/res/debug.png" << ":/res/info.png" <<
                          ":/res/warn.png" << ":/res/error.png" << ":/res/critical.png");

QStringList level_names = (QStringList() << "Trace" << "Debug" << "Info" << "Warning" << "Error" << "Critical" << "Off");

enum class Column { Level = 0, Logger, Time, Message, Last };

QStringList column_names = (QStringList() << "Level" << "Logger" << "Time" << "Message");

} // namespace

QSpdLogModel::QSpdLogModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

void QSpdLogModel::addEntry(entry_t entry)
{
    if (_maxEntries > 0 && _items.size() == _maxEntries) {
        beginRemoveRows(QModelIndex(), 0, 0);
        _items.pop_front();
        endRemoveRows();
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    _items.push_back(std::move(entry));

    endInsertRows();
}

void QSpdLogModel::setMaxEntries(nonstd::optional<std::size_t> maxEntries)
{
    _maxEntries = maxEntries;
    // Incase the new maximum is below the current amount of items.
    if (_maxEntries > 0 && _items.size() > _maxEntries) {
        std::size_t offset = _items.size() - _maxEntries.value();
        beginRemoveRows(QModelIndex(), 0, offset - 1);
        _items.erase(_items.begin(), _items.begin() + offset);
        endRemoveRows();
    }
}

nonstd::optional<std::size_t> QSpdLogModel::getMaxEntries() const
{
    return _maxEntries;
}

void QSpdLogModel::clear()
{
    beginResetModel();
    _items.clear();
    endResetModel();
}

int QSpdLogModel::rowCount(const QModelIndex& parent) const
{
    return _items.size();
}

int QSpdLogModel::columnCount(const QModelIndex& parent) const
{
    return static_cast<std::size_t>(Column::Last);
}

QVariant QSpdLogModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= _items.size())
        return QVariant();

    switch (role) {
        case Qt::DisplayRole: {
            auto const& item = _items[ index.row() ];
            switch (static_cast<Column>(index.column())) {
                case Column::Level: {
                    return QString(level_names[ item.level ]);
                }

                case Column::Logger: {
                    return QString::fromStdString(item.loggerName);
                }

                case Column::Time: {
                    return QDateTime::fromMSecsSinceEpoch(
                        std::chrono::duration_cast<std::chrono::milliseconds>(
                            item.time
                        )
                            .count()
                    );
                }

                case Column::Message: {
                    return QString::fromStdString(item.message);
                }

                default: {
                    break;
                }
            }

            break;
        }

        case Qt::DecorationRole: {
            if (index.column() == 0) {
                const auto& item = _items[ index.row() ];
                if (item.level >= 0 && item.level < icon_names.size()) {
                    return QIcon(
                        QString(icon_names[ _items[ index.row() ].level ])
                    );
                }
            }

            break;
        }

        case Qt::BackgroundRole: {
            std::string loggerName = _items[ index.row() ].loggerName;
            if (_backgroundMappings.contains(loggerName))
                return _backgroundMappings.value(loggerName);

            break;
        }

        case Qt::ForegroundRole: {
            std::string loggerName = _items[ index.row() ].loggerName;
            if (_foregroundMappings.contains(loggerName))
                return _foregroundMappings.value(loggerName);

            break;
        }

        case Qt::FontRole: {
            std::string loggerName = _items[ index.row() ].loggerName;
            if (_fontMappings.contains(loggerName))
                return _fontMappings.value(loggerName);

            break;
        }

        default: {
            break;
        }
    }

    return QVariant();
}

QVariant QSpdLogModel::headerData(
    int section, Qt::Orientation orientation, int role
) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return QString(column_names[ section ]);

    return QVariant();
}

void QSpdLogModel::setLoggerForeground(
    nonstd::string_view loggerName, nonstd::optional<QColor> color
)
{
    int lastRow = this->rowCount() - 1;
    if (lastRow < 0)
        lastRow = 0;
    int lastColumn = this->columnCount() - 1;
    if (lastColumn < 0)
        lastColumn = 0;
    if (color.has_value()) {
        _foregroundMappings[ loggerName.to_string() ] = color.value();
        emit dataChanged(
            this->index(0),
            this->index(lastRow, lastColumn),
            QVector<int>{ Qt::ForegroundRole }
        );
    } else if (_foregroundMappings.contains(loggerName.to_string())) {
        _foregroundMappings.remove(loggerName.to_string());
        emit dataChanged(
            this->index(0),
            this->index(lastRow, lastColumn),
            QVector<int>{ Qt::ForegroundRole }
        );
    }
}

nonstd::optional<QColor> QSpdLogModel::getLoggerForeground(
    nonstd::string_view loggerName
) const
{
    if (_foregroundMappings.contains(loggerName.to_string()))
        return _foregroundMappings.value(loggerName.to_string());

    return nonstd::nullopt;
}

void QSpdLogModel::setLoggerBackground(
    nonstd::string_view loggerName, nonstd::optional<QBrush> brush
)
{
    int lastRow = this->rowCount() - 1;
    if (lastRow < 0)
        lastRow = 0;
    int lastColumn = this->columnCount() - 1;
    if (lastColumn < 0)
        lastColumn = 0;
    if (brush.has_value()) {
        _backgroundMappings[ loggerName.to_string() ] = brush.value();
        emit dataChanged(
            this->index(0),
            this->index(lastRow, lastColumn),
            QVector<int>{ Qt::BackgroundRole }
        );
    } else if (_backgroundMappings.contains(loggerName.to_string())) {
        _backgroundMappings.remove(loggerName.to_string());
        emit dataChanged(
            this->index(0),
            this->index(lastRow, lastColumn),
            QVector<int>{ Qt::BackgroundRole }
        );
    }
}

nonstd::optional<QBrush> QSpdLogModel::getLoggerBackground(
    nonstd::string_view loggerName
) const
{
    if (_backgroundMappings.contains(loggerName.to_string()))
        return _backgroundMappings.value(loggerName.to_string());

    return nonstd::nullopt;
}

void QSpdLogModel::setLoggerFont(
    nonstd::string_view loggerName, nonstd::optional<QFont> font
)
{
    int lastRow = this->rowCount() - 1;
    if (lastRow < 0)
        lastRow = 0;
    int lastColumn = this->columnCount() - 1;
    if (lastColumn < 0)
        lastColumn = 0;
    if (font.has_value()) {
        _fontMappings[ loggerName.to_string() ] = font.value();
        emit dataChanged(
            this->index(0), this->index(lastRow, lastColumn), { Qt::FontRole }
        );
    } else if (_fontMappings.contains(loggerName.to_string())) {
        _fontMappings.remove(loggerName.to_string());
        emit dataChanged(
            this->index(0), this->index(lastRow, lastColumn), { Qt::FontRole }
        );
    }
}

nonstd::optional<QFont> QSpdLogModel::getLoggerFont(nonstd::string_view loggerName
) const
{
    if (_fontMappings.contains(loggerName.to_string()))
        return _fontMappings.value(loggerName.to_string());

    return nonstd::nullopt;
}
