/**
  * @file   evalplot.h
  * @author Jean-Philippe Meylan <jean-philippe.meylan_at_heig-vd.ch>
  * @author ReDS (Reconfigurable and embedded digital systems) <www.reds.ch>
  * @author HEIG-VD (Haute école d'ingénierie et de gestion) <www.heig-vd.ch>
  * @author Yvan Da Silva <yvan.dasilva_at_heig-vd.ch>
  * @date   06.2012
  * @date   03.2010
  * @section LICENSE
  *
  * This application is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Lesser General Public
  * License as published by the Free Software Foundation; either
  * version 3.0 of the License, or (at your option) any later version.
  *
  * This library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  * Lesser General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public
  * License along with this library; if not, write to the Free Software
  * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
  *
  * @class EvalPlot
  *
  * @brief This class implements the evaluation/validation/prediction plot. The interface
  * differs a bit according to the mode selected.
  */

#ifndef EVALPLOT_H
#define EVALPLOT_H

#include <QDialog>

#include <QLineSeries>
#include <QChart>
#include <QValueAxis>
#include <QChartView>
//#include <QScatterSeries>

/*
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_array.h>
#include <qwt_legend.h> */

namespace Ui {
    class EvalPlot;
}

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    using namespace QtCharts;
#endif


class EvalPlot : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(EvalPlot)
public:
    struct plotValues {
        // Default constructor will be needed if inserting into vector
        plotValues() : mesured(), expected(), predicted() {}

        plotValues( float m, float e, float p ) :
            mesured(m), expected(e), predicted(p) {}

        bool operator<( plotValues const& rPv ) const
           { return expected < rPv.expected; }

        float mesured;
        float expected;
        float predicted;
    };

    explicit EvalPlot(QWidget *parent = 0);
    virtual ~EvalPlot();
    void loadData(QList<QStringList>* sysData);
    void setNbOutVars(int nbOutVars);
    void setMesuredValues(QVector<float> mesValues);
    void setExpectedValues(QVector<float> expValues);
    void setPredictedValues(QVector<float> predValues);
    void setDescription(QString desc);
    void setPredictive(bool isPredict);
    void resetValues();
    void setFitness(float);
    void setSensitivity(float);
    void setSpecificity(float);
    void setAccuracy(float);
    void setPpv(float);
    void setRmse(float);
    //MODIF - BUJARD - 1.04.2010
    // add for regression problem
    void setRrse    (float);
    void setRae     (float);
    void setMse (float);
    void setAdm (float);
    void setMdm (float);
    void setSize (float);
    void setOverLearn (float);
    // FIN - MODIF - BUJARD - 1.04.2010
    void saveEval(QString fileName);

public slots:

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::EvalPlot *m_ui;
    QList<QStringList>* systemData;
    bool isPredictive;
    QVector<plotValues> sortedValues;
    QVector<float> mesuredValues;
    QVector<float> expectedValues;
    QVector<float> predictedValues;
    QVector<float> mesuredValuesOriginal;
    QVector<float> expectedValuesOriginal;
    QVector<float> predictedValuesOriginal;
    QVector<double>* xVals;
    QVector<double>* yValsMesured;
    QVector<double>* yValsExpected;
    QVector<double>* yValsPredicted;
    QVector<double>* yValsThresh;

    QChart* myPlot;
    QValueAxis* axisX;
    QValueAxis* axisY;
    QChartView* myPlotView;
    //QScatterSeries* valsMesured;
    QLineSeries* valsMesured;
    QLineSeries* valsExpected;
    QLineSeries* valsPredicted;
    QLineSeries* threshCurve;
    /* QWT-OLD-CODE
    QwtPlot* myPlot;
    QwtLegend* legend;
    QwtPlotCurve* valsMesured;
    QwtPlotCurve* valsExpected;
    QwtPlotCurve* valsPredicted;
    QwtPlotCurve* threshCurve; */

    QString desc;
    int nbOutVars;
    float fitness;
    float sensitivity;
    float specificity;
    float accuracy;
    float ppv;
    float rmse;
    float rrse;
    float rae;
    float mse;
    float adm;
    float mdm;
    float size;
    float overLearn;

    void affectMesuredValues(QVector<float> mesValues, int outVar);
    void affectExpectedValues(QVector<float> expValues);
    void affectPredictedValues(QVector<float> predValues);

private slots:
    void onSaveEval();
    void onCloseEval();
    void onSelectOut();
    void onSort();
};

#endif // EVALPLOT_H
