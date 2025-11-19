#pragma once

#include <QAbstractListModel>
#include <deque>
#include "qspdlog/optional.hpp"
#include "qspdlog/string_view.hpp"
#include <QFont>
#include <chrono>
#include <QBrush>

class QSpdLogModel : public QAbstractListModel
{
public:
    Q_OBJECT
public:
    struct entry_t {
        std::chrono::duration<double> time;
        int level;
        std::string message;
        std::string loggerName;
    };

public:
    QSpdLogModel(QObject* parent = nullptr);
    ~QSpdLogModel() override = default;

    void addEntry(entry_t entry);
    void clear();

    void setMaxEntries(nonstd::optional<std::size_t> maxEntries);
    nonstd::optional<std::size_t> getMaxEntries() const;

    void setLoggerForeground(nonstd::string_view loggerName, nonstd::optional<QColor> color);
    nonstd::optional<QColor> getLoggerForeground(nonstd::string_view loggerName) const;

    void setLoggerBackground(nonstd::string_view loggerName, nonstd::optional<QBrush> brush);
    nonstd::optional<QBrush> getLoggerBackground(nonstd::string_view loggerName) const;

    void setLoggerFont(nonstd::string_view loggerName, nonstd::optional<QFont> font);
    nonstd::optional<QFont> getLoggerFont(nonstd::string_view loggerName) const;

#pragma region QAbstractListModel
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)
        const override;
    QVariant headerData(
        int section, Qt::Orientation orientation, int role = Qt::DisplayRole
    ) const override;
#pragma endregion

private:
    std::deque<entry_t> _items;
    nonstd::optional<std::size_t> _maxEntries;
    QMap<std::string, QBrush> _backgroundMappings;
    QMap<std::string, QColor> _foregroundMappings;
    QMap<std::string, QFont> _fontMappings;
};
