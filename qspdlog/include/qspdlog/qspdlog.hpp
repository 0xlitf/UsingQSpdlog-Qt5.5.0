#pragma once
#define nssv_CONFIG_NO_CHAR16_T 1
#define nssv_CONFIG_NO_CHAR32_T 1
#define nssv_CONFIG_NO_UNICODE_LITERALS 1
#include "optional.hpp"
#include "string_view.hpp"
#include <memory>
// #include <gsl/gsl>
#include <QFont>
#include <QList>
#include <QWidget>

namespace spdlog
{
class logger;
namespace sinks
{
class sink;
} // namespace sinks
} // namespace spdlog

class QAbstractSpdLogToolBar;
class QMenu;
class QSpdLogModel;
class QSpdLogProxyModel;
class QTreeView;

enum class AutoScrollPolicy {
    AutoScrollPolicyDisabled =
        0, // Never scroll to the bottom, leave the scrollbar where it was.
    AutoScrollPolicyEnabled =
        1, // Always scroll to the bottom when new rows are inserted.
    AutoScrollPolicyEnabledIfBottom =
        2, // Scroll to the bottom only if the scrollbar was at the bottom
           // before inserting the new ones.
};

class QSpdLog : public QWidget
{
public:
    /**
     * @brief Constructor
     *
     * @param parent The parent widget.
     */
    explicit QSpdLog(QWidget* parent = nullptr);

    /**
     * @brief Destructor
     */
    ~QSpdLog();

public:
    /**
     * @brief Clear the contents of the model.
     *
     * The method will clear up all the cached messages. There's no way after
     * this to restore them.
     */
    void clear();

    /**
     * @brief Register a toolbar.
     *
     * The toolbar will be set up for the current instance. Being set up means
     * - all the actions from the toolbar will affect current instance
     * - the changes to one toolbar will be reflected in the other ones as well
     *
     * @param toolbar the toolbar
     */
    void registerToolbar(QAbstractSpdLogToolBar* toolbar);

    /**
     * @brief Remove a toolbar.
     *
     * The toolbar will be removed from the current instance. The toolbar will
     * not be deleted.
     *
     * @param toolbar the toolbar
     */
    void removeToolbar(QAbstractSpdLogToolBar* toolbar);

    /**
     * @brief Get the sink.
     *
     * The sink should be used by the user to add it into any logger whose
     * output the user want's to see in the widget.
     *
     * @return std::shared_ptr<spdlog::sinks::sink> the sink of the widget
     */
    std::shared_ptr<spdlog::sinks::sink> sink();

    /**
     * @brief Get the number of items in the widget.
     *
     * @return std::size_t the number of items in the widget
     */
    std::size_t itemsCount() const;

    /**
     * @brief Set the maximum number of items in the widget.
     *
     * @param nonstd::optional<std::size_t> the maximum number of items in the
     * widget
     */
    void setMaxEntries(nonstd::optional<std::size_t> maxEntries);

    /**
     * @brief Get the maximum number of items in the widget.
     *
     * @return nonstd::optional<std::size_t> the maximum number of items in the
     * widget
     */
    nonstd::optional<std::size_t> getMaxEntries() const;

    /**
     * @brief Set the foreground QBrush for the messages of the corresponding
     * logger.
     *
     * @param nonstd::string_view the name of the logger of which to set the
     * foreground brush
     * @param nonstd::optional<QBrush> the brush object or nonstd::nullopt
     */
    void setLoggerForeground(
        nonstd::string_view loggerName, nonstd::optional<QColor> brush
    );

    /**
     * @brief Get the foreground QBrush for the messages of the corresponding
     * logger.
     *
     * @param nonstd::string_view the name of the logger of which to get the
     * foreground brush from
     * @return nonstd::optional<QBrush> the QBrush object or nonstd::nullopt
     */
    nonstd::optional<QColor> getLoggerForeground(nonstd::string_view loggerName
    ) const;

    /**
     * @brief Set the background QBrush for the messages of the corresponding
     * logger.
     *
     * @param nonstd::string_view the name of the logger of which to set the
     * background brush
     * @param nonstd::optional<QBrush> the brush object or nonstd::nullopt
     */
    void setLoggerBackground(nonstd::string_view, nonstd::optional<QBrush> brush);

    /**
     * @brief Get the background QBrush for the messages of the corresponding
     * logger.
     *
     * @param nonstd::string_view the name of the logger of which to get the
     * background brush from
     * @return nonstd::optional<QBrush> the QBrush object or nonstd::nullopt
     */
    nonstd::optional<QBrush> getLoggerBackground(nonstd::string_view loggerName
    ) const;

    /**
     * @brief Set the text QFont for the messages of the corresponding
     * logger.
     *
     * @param nonstd::string_view the name of the logger of which to set the
     * font
     * @param nonstd::optional<QFont> the QFont object or nonstd::nullopt
     */
    void setLoggerFont(nonstd::string_view loggerName, nonstd::optional<QFont> font);

    /**
     * @brief Get the text QFont for the messages of the corresponding
     * logger.
     *
     * @param nonstd::string_view the name of the logger of which to get the
     * font from
     * @return nonstd::optional<QFont> the QFont object or nonstd::nullopt
     */
    nonstd::optional<QFont> getLoggerFont(nonstd::string_view loggerName) const;

    /**
     * @brief Set the policy of the auto-scrolling feature.
     *
     * This function will set the policy for auto-scrolling and will update all
     * the registered toolbars.
     *
     * @param policy the auto-scrolling policy
     */
    void setAutoScrollPolicy(AutoScrollPolicy policy);

private slots:
    void filterData(
        const QString& text, bool isRegularExpression, bool isCaseSensitive
    );
    void updateAutoScrollPolicy(int index);

private:
    QSpdLogModel* _sourceModel;
    QSpdLogProxyModel* _proxyModel;
    QTreeView* _view;
    bool _scrollIsAtBottom;
    QMetaObject::Connection _scrollConnection;
    std::shared_ptr<spdlog::sinks::sink> _sink;
    QList<QAbstractSpdLogToolBar*> _toolbars;
};
