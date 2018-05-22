#include "calcdialog.h"
#include "ui_calcdialog.h"

#include "main.h"
#include <QString>

calcDialog::calcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calcDialog)
{
    ui->setupUi(this);
	
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(pushButtonClicked()));
}

calcDialog::~calcDialog()
{
    delete ui;
}

void calcDialog::setModel(ClientModel *model)
{

}


void calcDialog::pushButtonClicked()
{
    QLocale us(QLocale::English, QLocale::UnitedStates);
    CBigNum bnMedianWeight = GetMedianWeightOverPeriod(1000);
    qint64 nMedianWeight = bnMedianWeight.getint();

    //set network text even if user amount is not valid
    QString strAvgSize = QString("The median weight staked over the last 1,000 blocks is ") + us.toString(bnMedianWeight.getuint());
    ui->avgWeightResult->setText(strAvgSize);

    if(ui->blockSizeEdit->text().isEmpty())
        return;

    int nTargetDays = ui->comboBoxTargetDays->currentText().toInt();
    QString strUserSize = ui->blockSizeEdit->text();
    int nUserAmount = strUserSize.toInt();

    //less than median weight
    if(nUserAmount * nTargetDays < nMedianWeight)
    {
        qint64 nUserWeightAtTarget = nUserAmount * nTargetDays;
        ui->avgWeightResult->setText(strAvgSize + QString(" It is recommended that you do not split your HYP. %1 HYP will yield a weight of <b>%2</b> on day %3, which is %4 less weight than the median weight staked in the last 1,000 blocks.")
                                     .arg(us.toString(nUserAmount))
                                     .arg(us.toString(nUserWeightAtTarget))
                                     .arg(us.toString(nTargetDays))
                                     .arg(us.toString(bnMedianWeight.getuint64() - nUserWeightAtTarget))
                                    );
        return;
    }

    int nSplitCount = nUserAmount * nTargetDays / nMedianWeight;
    int nRecommendedSize = nUserAmount / nSplitCount;
    qint64 nUserWeightAtTarget = nRecommendedSize * nTargetDays;
    ui->avgWeightResult->setText(strAvgSize + QString(" It is recommended that you split your %1 HYP into <b>%2 outputs of %3 HYP</b>. This will yield a weight of <b>%4</b> on day %5.")
                            .arg(us.toString(nUserAmount))
                            .arg(us.toString(nSplitCount))
                            .arg(us.toString(nRecommendedSize))
                            .arg(us.toString(nUserWeightAtTarget))
                            .arg(us.toString(nTargetDays))
                            );
}

void calcDialog::on_buttonBox_accepted()
{
	close();
}
