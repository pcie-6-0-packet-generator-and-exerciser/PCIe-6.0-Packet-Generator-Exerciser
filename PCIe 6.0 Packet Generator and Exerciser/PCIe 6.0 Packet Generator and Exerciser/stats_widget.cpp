#include "stats_widget.h"
#include "utils/tlp.h"
#include <QtCharts>
#include <QtWidgets/QFrame>

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>



using namespace Ui;

StatsWidget::StatsWidget(QWidget *parent ) 
	: QFrame(parent)
{
	memRead32 = 0;
	memWrite32 = 0;
	memRead64 = 0;
	memWrite64 = 0;
	configRead0 = 0;
	configRead1 = 0;
	configWrite0 = 0;
	configWrite1 = 0;

}

StatsWidget::~StatsWidget()
{
}
//int StatsWidget::memRead32 = 0;
//int StatsWidget::memWrite32 = 0;
//int StatsWidget::memRead64 = 0;
//int StatsWidget::memWrite64 = 0;
//int StatsWidget::configRead0 = 0;
//int StatsWidget::configWrite0 = 0;
//int StatsWidget::configRead1 = 0;
//int StatsWidget::configWrite1 = 0;
//void StatsWidget::initializeStats() {
//	memRead32 = 0;
//	memWrite32 = 0;
//	memRead64 = 0;
//	memWrite64 = 0;
//	configRead0 = 0;
//	configRead1 = 0;
//	configWrite0 = 0;
//	configWrite1 = 0;
//}
void StatsWidget::viewStats() {
	QPieSeries *series = new QPieSeries();
	series->append("MemRead32", memRead32);
	series->append("MemRead64", memRead64);
	series->append("MemWrite32", memWrite32);
	series->append("MemWrite64", memWrite64);
	series->append("ConfigRead0", configRead0);
	series->append("ConfigRead1", configRead1);
	series->append("ConfigWrite0", configWrite0);
	series->append("ConfigWrite1", configWrite1);

	QChart *chart = new QChart();
	chart->addSeries(series);
	chart->setTitle("TLP Statistics");

	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	//chartView->show();
}

 void StatsWidget::incStats(TLPType type)
{
	switch (type) {
	case TLPType::MemRead32:
		memRead32++;
		break;
	case TLPType::MemRead64:
		memRead64++;
		break;
	case TLPType::MemWrite32:	
		memWrite32++;
		break;
	case TLPType::MemWrite64:
		memWrite64++;
		break;
	case TLPType::ConfigRead0:
		configRead0++;
		break;
	case TLPType::ConfigWrite0:
		configWrite0++;
		break;
	case TLPType::ConfigRead1:
		configRead1++;
		break;
	case TLPType::ConfigWrite1:
		configWrite1++;
		break;
	default:
		break;
	}
	
}
void StatsWidget::decStats(TLPType type){
	switch (type) {
	case TLPType::MemRead32:
		memRead32--;
		break;
	case TLPType::MemRead64:
		memRead64--;
		break;
	case TLPType::MemWrite32:
		memWrite32--;
		break;
	case TLPType::MemWrite64:
		memWrite64--;
		break;
	case TLPType::ConfigRead0:
		configRead0--;
		break;
	case TLPType::ConfigWrite0:
		configWrite0--;
		break;
	case TLPType::ConfigRead1:
		configRead1--;
		break;
	case TLPType::ConfigWrite1:
		configWrite1--;
		break;
	default:
		break;
	}
}