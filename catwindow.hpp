#ifndef CATWINDOW_HPP
#define CATWINDOW_HPP

#include "catalanboard.hpp"
#include "catalanviz.hpp"

#include <QGraphicsScene>
#include <QMainWindow>

#include <memory>
#include <string>


namespace Ui {
class CatWindow;
}

class CatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CatWindow(QWidget *parent = 0);
    ~CatWindow();

private slots:
    void on_eastButton_clicked();

    void on_southButton_clicked();

    void on_undoButton_clicked();

    void on_clearButton_clicked();

    void on_randButton_clicked();

    void on_resizeButton_clicked();

    void on_quitButton_clicked();

    void on_vizSelectBox_currentIndexChanged(const QString &arg1);

    void on_dimensionBox_editingFinished();

private:
    Ui::CatWindow *ui;

    CatalanBoard catBoard;
    QGraphicsScene boardScene;

    std::unique_ptr<CatalanViz> visualizer;

    void setVisualizer(CatalanViz::Type vizType);

    void quickMessage(const std::string &message);

    void progBarUpdate();
    void dyckStringUpdate();
    void boardUpdate();
};

#endif // CATWINDOW_HPP
