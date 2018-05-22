#ifndef PROPOSALSDIALOG_H
#define PROPOSALSDIALOG_H

#include <QDialog>
#include <QObject>

class WalletModel;

namespace Ui {
class ProposalsDialog;
}

class ProposalsDialog : public QDialog
{
    Q_OBJECT
public:
    ProposalsDialog(QWidget *parent = 0);
    ~ProposalsDialog();
    void SetWalletModel(WalletModel* model);
    void UpdateTable();
private slots:
    void on_checkBox_Active_stateChanged(int arg1);
    void on_checkBox_Upcoming_stateChanged(int arg1);
    void on_checkBox_Finished_stateChanged(int arg1);

private:
    Ui::ProposalsDialog *ui;
    WalletModel* walletModel;
};

#endif // PROPOSALSDIALOG_H
