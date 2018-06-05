# Tedcoin Immutable Voting System

Copyright (c) 2014-2018 TedLab Sciences Ltd
Copyright (c) 2011-2012 Bitcoin Developers
Distributed under the MIT/X11 software license, see the accompanying file license.txt or http://www.opensource.org/licenses/mit-license.php. This product includes software developed by the OpenSSL Project for use in the OpenSSL Toolkit (http://www.openssl.org/).

Introduction
------------
Tedcoin is a immutable voting system project, with the goal of providing a long-term energy-efficient Proof of Stake based cryptocurrency. Built on the foundation of Bitcoin, innovations such as proof-of-stake help further advance the field of cryptocurrency.

Tedcoin is an advanced blockchain platform that provides generous rewards to users for securing the blockchain without the need for complicated mining equipment. Tedcoin focuses on being the leading Proof of Stake currency to use for long term value storage. Rewards help ensure that your cryptocurrency portfolio is being put to work instead of laying dormant and potentially losing value. Advanced staking tools within the wallet allow users to have complete control over their staking strategy and ability to maximize investment returns. Tedcoin has the most advanced wallet and tools for staking available anywhere.

Tedcoin uses a proof of stake based consensus system that is designed to reward long-term participants within the Tedcoin ecosystem. Rewards are based on the amount of coins that a user holds, as well as how old those coins are. Larger and older coins are more likely to stake.

Tedchain provides the ability to securely communicate between devices running the Tedcoin wallet. Secure communication between users can occur between single users or between groups. Tedchain provides a platform for users to create channels that broadcast signals and data into Tedcoin's blockchain. It allows for small amounts of immutable data to be added to the blockchain. Only Tedcoin users will be able to securely communicate with each other.

Many popular digital currencies have difficulty with governance and how to make decisions on changing aspects about the coin. Tedcoin seeks to solve this issue with the implementation of an immutable voting system, which is accessible to any user that actively stakes. A proposal is made based on an identified issue that a user or group may face and is added to the blockchain to be voted on. Users with the most to gain or lose from important decisions about Tedcoin will be those with the largest sway on the overall vote.

Setup
-----
Unpack the files into a directory and run:

	bin/32/tedcoind (headless, 32-bit)
	bin/64/tedcoind (headless, 64-bit)

The software automatically finds other nodes to connect to.  You can enable Universal Plug and Play (UPnP) with your router/firewall or forward port 

18775 (TCP) to your computer so you can receive incoming connections. Tedcoin works without incoming connections, but allowing incoming connections helps the Tedcoin network.

Upgrade
-------
All you existing coins/transactions should be intact with the upgrade.
To upgrade first backup wallet

	tedcoind backupwallet <destination_backup_file>

Then shutdown tedcoind by
	
	tedcoind stop

Start up the new tedcoind.

See the tedcoin site:  http://tedchain.network for help and more information.

Build Instructions (Linux)
--------------------------
### Dependencies required for Tedcoin with or without GUI:

	sudo apt-get install build-essential libtool autotools-dev autoconf pkg-config libssl-dev libboost-all-dev libdb5.3-dev libdb5.3++-dev libminiupnpc-dev automake
	./autogen.sh

### Configure without GUI:

	./configure --with-incompatible-bdb --with-gui=no

### Configure with GUI:

	sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler libqrencode-dev
	./configure --with-incompatible-bdb --with-gui=qt5

### Compile
	make
