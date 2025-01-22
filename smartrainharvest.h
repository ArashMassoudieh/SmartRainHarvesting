#ifndef SMARTRAINHARVEST_H
#define SMARTRAINHARVEST_H

#include <QMainWindow>
#include "noaaweatherfetcher.h"
#include "chartcontainer.h"
#include "DistanceSensor.h"
#include "QTimer"

QT_BEGIN_NAMESPACE
namespace Ui { class SmartRainHarvest; }
QT_END_NAMESPACE

class QChartView;

class SmartRainHarvest : public QMainWindow
{
    Q_OBJECT

public:
    SmartRainHarvest(QWidget *parent = nullptr);
    ~SmartRainHarvest();
    QVector<WeatherData> cummulativerain;
    QVector<WeatherData> depth;
    double max_distance = 100;
    double waterdepthcriteria = 50;
    double cummulativeraincriteria = 50;
    double bypassdepthcriteria = 100;
    double depthtoreleaseto = 75;
    double minumumdepth = 5;
    void StartRelease();
private:
    Ui::SmartRainHarvest *ui;
    NOAAWeatherFetcher fetcher;
    int latitude = 97;
    int longitude = 71;
    ChartContainer *ProbnQuanChartContainer = new ChartContainer();
    ChartContainer *CummulativeForcastChartContainer = new ChartContainer();
    ChartContainer *WaterDepthChartContainer = new ChartContainer();
    DistanceSensor distancesensor;
    QTimer *ReleaseTimer = new QTimer();
    void ShutTheValve();
    void OpenTheValve();
    bool overflow = false;
public slots:
    void on_Check_Timer();
    void on_Check_Distance();


};
#endif // SMARTRAINHARVEST_H
