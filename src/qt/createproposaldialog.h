#ifndef CREATEPROPOSALDIALOG_H
#define CREATEPROPOSALDIALOG_H

#include <QDialog>
#include <QObject>

class WalletModel;
class CVoteProposal;

namespace Ui {
class CreateProposalDialog;
}

class CreateProposalDialog : public QDialog
{
    Q_OBJECT
public:
    CreateProposalDialog(QWidget* parent);
    ~CreateProposalDialog();
    void SetWalletModel(WalletModel* model);
private slots:
    void on_button_CreateProposal_clicked();
    void on_button_SendProposal_clicked();
private:
    Ui::CreateProposalDialog* ui;
    WalletModel* walletModel;
    CVoteProposal* proposal;
    void Clear();
};

#endif // CREATEPROPOSALDIALOG_H
