#ifndef BITCOINGUI_H
#define BITCOINGUI_H

#include <QMainWindow>
#include <QSystemTrayIcon>

#include "util.h" // for uint64

class AddressBookPage;
class BlockBrowser;
class ClientModel;
class NetworkStyle;
class Notificator;
class OverviewPage;
class RPCConsole;
class SendCoinsDialog;
class SignVerifyMessageDialog;
class Bip38ToolDialog;
class StakeForCharityDialog;
class TransactionTableModel;
class TransactionView;
class WalletModel;
class VotingDialog;

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QTableView;
class QAbstractItemModel;
class QModelIndex;
class QProgressBar;
class QStackedWidget;
class QUrl;
QT_END_NAMESPACE

/**
  Bitcoin GUI main class. This class represents the main window of the Bitcoin UI. It communicates with both the client and
  wallet models to give the user an up-to-date view of the current core state.
*/
class BitcoinGUI : public QMainWindow
{
    Q_OBJECT
public:
    explicit BitcoinGUI(const NetworkStyle *networkStyle, QWidget *parent = 0);
    ~BitcoinGUI();

    /** Set the client model.
        The client model represents the part of the core that communicates with the P2P network, and is wallet-agnostic.
    */
    void setClientModel(ClientModel *clientModel);
    /** Set the wallet model.
        The wallet model represents a bitcoin wallet, and offers access to the list of transactions, address book and sending
        functionality.
    */
    void setWalletModel(WalletModel *walletModel);

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    ClientModel *clientModel;
    WalletModel *walletModel;

    QStackedWidget *centralWidget;

    OverviewPage *overviewPage;
    QWidget *transactionsPage;
    AddressBookPage *addressBookPage;
    AddressBookPage *receiveCoinsPage;
    SendCoinsDialog *sendCoinsPage;
    SignVerifyMessageDialog *signVerifyMessageDialog;
    Bip38ToolDialog *bip38Dialog;
	StakeForCharityDialog *stakeForCharityDialog;
	BlockBrowser *blockBrowser;
    VotingDialog* votingDialog;

    QLabel *labelEncryptionIcon;
    QLabel *labelMintingIcon;
    QLabel *labelConnectionsIcon;
    QLabel *labelBlocksIcon;
    QLabel *progressBarLabel;
    QProgressBar *progressBar;

    QMenuBar *appMenuBar;
    QAction *overviewAction;
    QAction *historyAction;
    QAction *quitAction;
    QAction *sendCoinsAction;
    QAction *addressBookAction;
    QAction *signMessageAction;
    QAction *verifyMessageAction;
    QAction *aboutAction;
    QAction *receiveCoinsAction;
    QAction *optionsAction;
    QAction *toggleHideAction;
    QAction *exportAction;
    QAction *encryptWalletAction;
	QAction *unlockWalletAction;
    QAction *backupWalletAction;
    QAction *changePassphraseAction;
    QAction *lockWalletToggleAction;
    QAction *bip38ToolAction;
	QAction *checkWalletAction;
	QAction *repairWalletAction;
    QAction *aboutQtAction;
    QAction *themeCustomAction;
    QAction *openRPCConsoleAction;
	QAction *blockAction;
	QAction *blocksIconAction;
	QAction *connectionIconAction;
	QAction *stakingIconAction;
	QAction *charityAction;
	QAction *calcAction;
    QAction *votingAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    Notificator *notificator;
    TransactionView *transactionView;
    RPCConsole *rpcConsole;

    QMovie *syncIconMovie;
    QMovie *miningIconMovie;

    uint64 nMinMax;
    uint64 nWeight;
    uint64 nNetworkWeight;
	uint64 nHoursToMaturity;
	uint64 nAmount;
	bool fMultiSend;
	bool fMultiSendNotify;
	int nCharityPercent;
	QString strCharityAddress;
    /* Themes support */
    QString selectedTheme;
    QStringList themesList;
    // Path to directory where all themes are (usable for some common images?...)
    QString themesDir;
    QAction *customActions[100];
    /* /Themes support */

    /** Create the main UI actions. */
    void createActions();
    /** Create the menu bar and sub-menus. */
    void createMenuBar();
    /** Create the toolbars */
    void createToolBars();
    /** Create system tray icon and notification */
    void createTrayIcon(const NetworkStyle *networkStyle);
    /** Create system tray menu (or setup the dock menu) */
    void createTrayIconMenu();


public slots:
    /** Set number of connections shown in the UI */
    void setNumConnections(int count);
    /** Set number of blocks shown in the UI */
    void setNumBlocks(int count, int nTotalBlocks);
    /** Set the encryption status as shown in the UI.
       @param[in] status            current encryption status
       @see WalletModel::EncryptionStatus
    */
    void setEncryptionStatus(int status);

    /** Notify the user of an error in the network or transaction handling code. */
    void error(const QString &title, const QString &message, bool modal);
    /** Asks the user whether to pay the transaction fee or to cancel the transaction.
       It is currently not possible to pass a return value to another thread through
       BlockingQueuedConnection, so an indirected pointer is used.
       https://bugreports.qt-project.org/browse/QTBUG-10440

      @param[in] nFeeRequired       the required fee
      @param[out] payFee            true to pay the fee, false to not pay the fee
    */
    void askFee(qint64 nFeeRequired, bool *payFee);
    void handleURI(QString strURI);

private slots:
    /** Switch to overview (home) page */
    void gotoOverviewPage();
    /** Switch to history (transactions) page */
    void gotoHistoryPage();
    /** Switch to address book page */
    void gotoAddressBookPage();
    /** Switch to receive coins page */
    void gotoReceiveCoinsPage();
    /** Switch to send coins page */
    void gotoSendCoinsPage();
	/** Switch to block browser page */
	void gotoBlockBrowser(QString transactionId = "");
    /** Show Sign/Verify Message dialog and switch to sign message tab */
    void gotoSignMessageTab(QString addr = "");
    /** Show Sign/Verify Message dialog and switch to verify message tab */
    void gotoVerifyMessageTab(QString addr = "");
    /** Show BIP 38 tool - default to Encryption tab */
    void gotoBip38Tool();
    /** Show the voting dialog */
    void gotoVotingDialog();
	/** Allow user to unlock wallet from click */
	void lockIconClicked();
    /** Show configuration dialog */
    void optionsClicked();
    /** Show about dialog */
    void aboutClicked();
	/** Show Stake Calculator Dialog */
    void calcClicked();
#ifndef Q_OS_MAC
    /** Handle tray icon clicked */
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
#endif
    /** Show incoming transaction notification for new transactions.

        The new items are those between start and end inclusive, under the given parent item.
    */
    void incomingTransaction(const QModelIndex & parent, int start, int end);
    /** Encrypt the wallet */
    void encryptWallet(bool status);
	/** Check the wallet */
	void checkWallet();
	/** Repair the wallet */
	void repairWallet();
    /** Backup the wallet */
    void backupWallet();
    /** Change encrypted wallet passphrase */
    void changePassphrase();
	/** Lock Wallet */
	void lockWallet();
    /** Toggle unlocking wallet temporarily */
    void lockWalletToggle();
	/** Ask for passphrase to unlock wallet temporarily */
	void unlockWallet();
	/** Ask for passphrase to unlock wallet for the session to mint */
	void unlockWalletForMint();
    /** Show window if hidden, unminimize when minimized, rise when obscured or show if hidden and fToggleHidden is true */
    void showNormalIfMinimized(bool fToggleHidden = false);
    /** simply calls showNormalIfMinimized(true) for use in SLOT() macro */
    void toggleHidden();

    /** Update info about minting */
    void updateMintingIcon();
    /** Update minting weight info */
    void updateMintingWeights();
	void charityClicked(QString addr = "");
    /** Load external QSS stylesheet */
    void changeTheme(QString theme);
    void loadTheme(QString theme);
    void listThemes(QStringList& themes);
    void keyPressEvent(QKeyEvent * e);
};

#endif
