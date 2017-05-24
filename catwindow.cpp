#include "catwindow.hpp"
#include "ui_catwindow.h"

#include "pathviz.hpp"
#include "triangviz.hpp"

#include <sstream>

namespace {
template<typename T, typename ...Args>
std::unique_ptr<T> my_make_unique(Args&& ...args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}


CatWindow::CatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CatWindow),
    catBoard(5),
    boardScene(),
    visualizer{my_make_unique<PathViz>(catBoard, boardScene)}
{
    setStatusBar(new QStatusBar);

    ui->setupUi(this);
    ui->graphicsView->setScene(&boardScene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    visualizer->drawSkeleton();
}

CatWindow::~CatWindow()
{
    delete ui;
}

void CatWindow::quickMessage(const std::string &message)
{
    statusBar()->showMessage(QString::fromStdString(message), 2000);
}

void CatWindow::progBarUpdate()
{
    const auto &cursor = catBoard.currentPos();

    ui->eastBar->setValue(cursor.x);
    ui->southBar->setValue(cursor.y);
}

void CatWindow::dyckStringUpdate()
{
    auto dyckStr = catBoard.pathString();
    if (dyckStr.empty()) {
        ui->dyckWord->setText("(No path specified)");
        return;
    }

    auto counter = 0;
    const auto newLine = 5;

    QString result{};
    QChar rightArrow(10145);
    QChar downArrow(11015);

    for (char c : dyckStr) {
        result.push_back(c == 'e' ? rightArrow : downArrow);
        result.push_back(' ');

        ++counter;
        if (counter % newLine == 0)
            result.push_back('\n');
    }
    ui->dyckWord->setText(result);
}

void CatWindow::boardUpdate()
{
    progBarUpdate();
    dyckStringUpdate();
    visualizer->drawViz();
}

void CatWindow::on_eastButton_clicked()
{
    if (catBoard.makeMove(CatalanBoard::Direc::east)) {
        boardUpdate();
        quickMessage("Moved east.");
    } else
        quickMessage("Illegal move!");
}

void CatWindow::on_southButton_clicked()
{
    if (catBoard.makeMove(CatalanBoard::Direc::south)) {
        boardUpdate();
        quickMessage("Moved south.");
    } else
        quickMessage("Illegal move!");
}

void CatWindow::on_undoButton_clicked()
{
    const auto &moveList = catBoard.currentPath();

    if (moveList.empty()) {
        quickMessage("Nothing to undo!");
        return;
    }

    catBoard.undoMove();

    boardUpdate();
    quickMessage("Undo!");
}



void CatWindow::on_clearButton_clicked()
{
    catBoard.clear();

    boardUpdate();
    quickMessage("Cleared board.");
}

void CatWindow::on_randButton_clicked()
{
    catBoard.random();

    boardUpdate();

    quickMessage("Randomly generated a path.");
}

void CatWindow::on_resizeButton_clicked()
{
    catBoard.resize(ui->dimensionBox->value());

    boardScene.clear();

    ui->eastBar->setMaximum(catBoard.dimension());
    ui->southBar->setMaximum(catBoard.dimension());
    boardUpdate();

    quickMessage("Resized the board.");
}

void CatWindow::on_quitButton_clicked()
{
    quickMessage("Goodbye!");
    QCoreApplication::quit();
}

void CatWindow::on_vizSelectBox_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "Catalan Path")
        visualizer = my_make_unique<PathViz>(catBoard, boardScene);
    else if (arg1 == "Polygon Triangulation")
        visualizer = my_make_unique<TriangViz>(catBoard, boardScene);

    boardScene.clear();
    visualizer->drawViz();
}

void CatWindow::on_dimensionBox_editingFinished()
{
    on_resizeButton_clicked();
}
