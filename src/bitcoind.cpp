#include "bitcoinrpc.h"
#include "init.h"
#include <boost/algorithm/string/predicate.hpp>

//////////////////////////////////////////////////////////////////////////////
//
// Start
//
bool AppInit(int argc, char* argv[])
{
    bool fRet = false;
    try
    {
        //
        // Parameters
        //
        // If Qt is used, parameters/bitcoin.conf are parsed in qt/bitcoin.cpp's main()
        ParseParameters(argc, argv);
        if (!boost::filesystem::is_directory(GetDataDir(false)))
        {
            fprintf(stderr, "Error: Specified directory does not exist\n");
            Shutdown(NULL);
        }
        ReadConfigFile(mapArgs, mapMultiArgs);
        
        if (mapArgs.count("-?") || mapArgs.count("--help"))
        {
            // First part of help message is specific to bitcoind / RPC client
            std::string strUsage = _("Tedcoin version") + " " + FormatFullVersion() + "\n\n" +
            _("Usage:") + "\n" +
            "  Tedcoind [options]                     " + "\n" +
            "  Tedcoind [options] <command> [params]  " + _("Send command to -server or Tedcoind") + "\n" +
            "  Tedcoind [options] help                " + _("List commands") + "\n" +
            "  Tedcoind [options] help <command>      " + _("Get help for a command") + "\n";
            
            strUsage += "\n" + HelpMessage();
            
            fprintf(stdout, "%s", strUsage.c_str());
            return false;
        }
        
        // Command-line RPC
        for (int i = 1; i < argc; i++)
            if (!IsSwitchChar(argv[i][0]) && !boost::algorithm::istarts_with(argv[i], "Tedcoin:"))
                fCommandLine = true;
        
        if (fCommandLine)
        {
            int ret = CommandLineRPC(argc, argv);
            exit(ret);
        }
        
        fRet = AppInit2();
    }
    catch (std::exception& e) {
        PrintException(&e, "AppInit()");
    } catch (...) {
        PrintException(NULL, "AppInit()");
    }
    if (!fRet)
        Shutdown(NULL);
    return fRet;
}

extern void noui_connect();
int main(int argc, char* argv[])
{
    bool fRet = false;
    fHaveGUI = false;

    
    // Connect bitcoind signal handlers
    noui_connect();
    
    fRet = AppInit(argc, argv);
    
    if (fRet && fDaemon)
        return 0;
    
    return 1;
}