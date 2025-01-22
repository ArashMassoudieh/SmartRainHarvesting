#include "smartrainharvest.h"
#include "ui_smartrainharvest.h"
#include "noaaweatherfetcher.h"
#include "chartcontainer.h"
#include <QMap>
#include <QTimer>
#include <DistanceSensor.h>

//QT_CHARTS_USE_NAMESPACE

SmartRainHarvest::SmartRainHarvest(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SmartRainHarvest)
{
    ui->setupUi(this);


    //Latitude 38.9072° N
    //Longitude: 77.0369 W

    QTimer *CheckWeatherTimer = new QTimer();

    connect(CheckWeatherTimer,SIGNAL(timeout()), this, SLOT(on_Check_Timer()));
    connect(ReleaseTimer,SIGNAL(timeout()), this, SLOT(on_Check_Distance()));

    CheckWeatherTimer->start(5000);

    ui->gridLayout->addWidget(ProbnQuanChartContainer->GetChartView(),0,0);
    ui->gridLayout->addWidget(CummulativeForcastChartContainer->GetChartView(),1,0);
    ui->gridLayout->addWidget(WaterDepthChartContainer->GetChartView(),2,0);

    distancesensor.initialize();
    on_Check_Timer();

}

SmartRainHarvest::~SmartRainHarvest()
{
    delete ui;
}

void SmartRainHarvest::on_Check_Timer()
{

    qDebug()<<"Checking weather!";
    QMap<QString, QVector<WeatherData>> precip_data;

    QVector<WeatherData> rainamountdata = fetcher.getWeatherPrediction(latitude, longitude, datatype::PrecipitationAmount);
    precip_data["Precipitation [mm]"] = rainamountdata;

    QVector<WeatherData> rainprobdata = fetcher.getWeatherPrediction(latitude, longitude, datatype::ProbabilityofPrecipitation);
    precip_data["Precipitation probability (%)"] = rainprobdata;

    QVector<WeatherData> tempdata = fetcher.getWeatherPrediction(latitude, longitude, datatype::Temperature);
    precip_data["Temperature (<sup>o</sup>C)"] = tempdata;

    ProbnQuanChartContainer->plotWeatherDataMap(precip_data);
    ProbnQuanChartContainer->GetChartView()->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout->addWidget(ProbnQuanChartContainer->GetChartView(),0,0);

    if (cummulativerain.count()>30) cummulativerain.removeFirst();

    cummulativerain.append({QDateTime::currentDateTime(),calculateCumulativeValue(rainamountdata,2) });
    CummulativeForcastChartContainer->plotWeatherData(cummulativerain,"Cummulative rain forecast [mm]");

    double distance = distancesensor.getDistance();

    if (depth.count()>30) cummulativerain.removeFirst();
    depth.append({QDateTime::currentDateTime(), max_distance - distance});
    WaterDepthChartContainer->plotWeatherData(depth, "Water Depth (cm)");

    if (depth.last().value>waterdepthcriteria && cummulativerain.last().value>cummulativeraincriteria)
    {
        overflow = false;
        StartRelease();
    }

    if (depth.last().value>bypassdepthcriteria)
    {
        overflow = true;
        StartRelease();
    }

}

void SmartRainHarvest::StartRelease()
{
    ReleaseTimer->start(10000);
}

void SmartRainHarvest::on_Check_Distance()
{
    double distance = distancesensor.getDistance();
    if (depth.count()>30) cummulativerain.removeFirst();
    depth.append({QDateTime::currentDateTime(), max_distance - distance});
    WaterDepthChartContainer->plotWeatherData(depth, "Water Depth (cm)");
    if (depth.last().value<(overflow?depthtoreleaseto:minumumdepth))
    {
        ReleaseTimer->stop();
        ShutTheValve();
    }
    else
    {
        OpenTheValve();
    }
}

void SmartRainHarvest::OpenTheValve(){

}

void SmartRainHarvest::ShutTheValve(){

}

