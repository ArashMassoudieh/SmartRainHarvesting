#ifndef CHARTCONTAINER_H
#define CHARTCONTAINER_H
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QDateTimeAxis>
#include <QMap>

#include "noaaweatherfetcher.h"

class ChartContainer
{
public:
    ChartContainer();
    void plotWeatherData(const QVector<WeatherData>& weatherData, const QString& yAxisTitle);
    void plotWeatherDataMap(const QMap<QString, QVector<WeatherData>>& weatherDataMap);
    QChartView *GetChartView() {return chartview;}
private:
    QChart *chart = new QChart();
    QChartView *chartview = new QChartView();
    void removeAllAxes();
};

#endif // CHARTCONTAINER_H
