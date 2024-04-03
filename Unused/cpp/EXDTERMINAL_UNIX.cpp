#include <QApplication>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QKeyEvent>
#include <QProcess>
#include <QTabWidget>
#include <QMenuBar>
#include <QAction>
#include <QSettings>
#include <QStyleFactory>
#include <QPalette>
#include <QDebug>
#include <QTextCursor>
#include <unistd.h> // For sleep

class CustomTerminal : public QWidget {
    Q_OBJECT
public:
    CustomTerminal(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        tabWidget = new QTabWidget(this);
        layout->addWidget(tabWidget);

        // Create a new tab with a terminal
        createTerminalTab();

        // Add menu bar
        createMenuBar();

        // Apply system palette and font
        applySystemPaletteAndFont();

        // Start the terminal process
        startTerminalProcess();
    }

protected:
    void keyPressEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_Up) {
            handleCommandHistory(true);
        } else if (event->key() == Qt::Key_Down) {
            handleCommandHistory(false);
        } else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            executeCommand();
        } else {
            QWidget::keyPressEvent(event);
        }
    }

private slots:
    void executeCommand() {
        QString command = getCurrentTerminalInput()->text();
        QProcess process;
        process.start(command);
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
        getCurrentTerminalOutput()->append(command);
        getCurrentTerminalOutput()->append(output);
        addCommandToHistory(command);
        getCurrentTerminalInput()->clear();
    }

    void changeFont() {
        // Handle font change
    }

    void changeTheme() {
        // Handle theme change
    }

    void createTerminalTab() {
        QWidget *terminalTab = new QWidget(this);
        QVBoxLayout *terminalLayout = new QVBoxLayout(terminalTab);
        terminalOutput = new QTextEdit(terminalTab);
        terminalOutput->setReadOnly(true);
        terminalInput = new QLineEdit(terminalTab);
        terminalLayout->addWidget(terminalOutput);
        terminalLayout->addWidget(terminalInput);
        tabWidget->addTab(terminalTab, "Terminal");
        terminalInput->setFocus();
    }

    void createMenuBar() {
        QMenuBar *menuBar = new QMenuBar(this);
        QMenu *fileMenu = menuBar->addMenu("&File");
        QAction *newTabAction = fileMenu->addAction("&New Tab");
        connect(newTabAction, &QAction::triggered, this, &CustomTerminal::createTerminalTab);

        QMenu *viewMenu = menuBar->addMenu("&View");
        QAction *fontAction = viewMenu->addAction("&Change Font");
        connect(fontAction, &QAction::triggered, this, &CustomTerminal::changeFont);
        QAction *themeAction = viewMenu->addAction("&Change Theme");
        connect(themeAction, &QAction::triggered, this, &CustomTerminal::changeTheme);

        setMenuBar(menuBar);
    }

    QTextEdit* getCurrentTerminalOutput() {
        QWidget *currentWidget = tabWidget->currentWidget();
        return qobject_cast<QTextEdit*>(currentWidget->layout()->itemAt(0)->widget());
    }

    QLineEdit* getCurrentTerminalInput() {
        QWidget *currentWidget = tabWidget->currentWidget();
        return qobject_cast<QLineEdit*>(currentWidget->layout()->itemAt(1)->widget());
    }

    void applySystemPaletteAndFont() {
        QPalette palette = qApp->palette();
        setPalette(palette);
        QFont font = qApp->font();
        setFont(font);
    }

    void handleCommandHistory(bool up) {
        if (up) {
            if (commandHistoryIndex > 0) {
                commandHistoryIndex--;
            }
        } else {
            if (commandHistoryIndex < commandHistory.size() - 1) {
                commandHistoryIndex++;
            }
        }
        if (!commandHistory.isEmpty()) {
            getCurrentTerminalInput()->setText(commandHistory.at(commandHistoryIndex));
        }
    }

    void addCommandToHistory(const QString& command) {
        if (!command.trimmed().isEmpty()) {
            commandHistory.prepend(command);
            commandHistoryIndex = 0;
        }
    }

    void startTerminalProcess() {
        // Simulate terminal process output
        QProcess process;
        process.start("sh");
        process.waitForStarted();
        process.write("echo 'Welcome to Custom Terminal!'\n");
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
        getCurrentTerminalOutput()->append(output);
    }

private:
    QTabWidget *tabWidget;
    QTextEdit *terminalOutput;
    QLineEdit *terminalInput;
    QStringList commandHistory;
    int commandHistoryIndex = 0;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    CustomTerminal terminal;
    terminal.show();
    return app.exec();
}

#include "main.moc"
