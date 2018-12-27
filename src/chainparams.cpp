// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Bitcoin Green developers
// Copyright (c) 2018 The Dachcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of (0, uint256("0x0000060041642648c0cb6dc68b7c66645c5e39144cc3dc1cac7726c93e74fa9f"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1535274000, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x000006a645f816b89fe77f540d65ebea9d37aa35da8690f588395d05fbd9435f"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1535274001,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x0000008045bd20aed2df810b292e36f495b4b5bfe6b33e4a9a5e1b747164fc4b"));
	
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1535274002,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xdd;
        pchMessageStart[1] = 0x6c;
        pchMessageStart[2] = 0xf0;
        pchMessageStart[3] = 0x04;
        vAlertPubKey = ParseHex("0400acad3e94eea458d6553f77c155ba5c02f4510273433879cd052af61b9b552539ef93909f8d4455664c32443300cc3fb67ae5dd10ce9fb0ecaa464bc422fa04");
        nDefaultPort = 31601;
        bnProofOfWorkLimit = ~uint256(0) >> 16;
        nSubsidyHalvingInterval = 1050000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Dachcoin: 1 day
        nTargetSpacing = 1 * 60;  // Dachcoin: 1 minutes
        nMaturity = 10;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 38000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 500;
        nModifierUpdateBlock = 1; // we use the version 2 for DACH

        /**
        python ~/GenesisH0new/genesis.py -a quark-hash -z "Mars is home to the tallest mountain in the solar system" -t 1535274000 -p 04d6a1c7390eca9630026f945986aa2c4a226cec7964e46100df576c672f4f017a301ad10fef98d89b9f44124b7117de1bcbdef33c83c90a2a9911c7a2fa70336a -v 0
		04ffff001d0104384d61727320697320686f6d6520746f207468652074616c6c657374206d6f756e7461696e20696e2074686520736f6c61722073797374656d
		algorithm: quark-hash
		merkle hash: 4a76c6ef834564439989f8fb208831399160fcfb5d093ca30b1220a25c6bd17b
		pszTimestamp: Mars is home to the tallest mountain in the solar system
		pubkey: 04d6a1c7390eca9630026f945986aa2c4a226cec7964e46100df576c672f4f017a301ad10fef98d89b9f44124b7117de1bcbdef33c83c90a2a9911c7a2fa70336a
		time: 1535274000
		bits: 0x1e0ffff0
		Searching for genesis hash..
		38760.0 hash/s, estimate: 30.8 hgenesis hash found!
		nonce: 2298761
		genesis hash: 0000060041642648c0cb6dc68b7c66645c5e39144cc3dc1cac7726c93e74fa9f
         */
        const char* pszTimestamp = "Mars is home to the tallest mountain in the solar system";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04d6a1c7390eca9630026f945986aa2c4a226cec7964e46100df576c672f4f017a301ad10fef98d89b9f44124b7117de1bcbdef33c83c90a2a9911c7a2fa70336a") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1535274000;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 2298761;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000060041642648c0cb6dc68b7c66645c5e39144cc3dc1cac7726c93e74fa9f"));
        assert(genesis.hashMerkleRoot == uint256("0x4a76c6ef834564439989f8fb208831399160fcfb5d093ca30b1220a25c6bd17b"));

        // DNS Seeding
        vSeeds.push_back(CDNSSeedData("seed1.dachcoin.live", "seed1.dachcoin.live"));
        vSeeds.push_back(CDNSSeedData("seed2.dachcoin.live", "seed2.dachcoin.live"));
		vSeeds.push_back(CDNSSeedData("seed3.dachcoin.live", "seed3.dachcoin.live"));
		vSeeds.push_back(CDNSSeedData("seed4.dachcoin.live", "seed4.dachcoin.live"));

        // Dachcoin addresses start with 'D'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 30);
        // Dachcoin script addresses start with '8'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);
        // Dachcoin private keys start with 'C'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 28);
        // Dachcoin BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Dachcoin BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "047d4136504b2568f24b1f35eb20416be10ec319562a2f84ca55736cf92c503bf28ab5e682385d9a76da5b7891d72f7d972baa5fae285c5ea594f7f1ee933d327b";
        strMasternodePoolDummyAddress = "DEKDMyd3vzWzzDaz3SQ1jTP4kxWFfPiGh7";
        nStartMasternodePayments = genesis.nTime + 14400; // 3 hours after genesis creation

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xed;
        pchMessageStart[1] = 0x7d;
        pchMessageStart[2] = 0xb1;
        pchMessageStart[3] = 0x05;
        vAlertPubKey = ParseHex("042f19826cc5bf9bdcf91f12e24fce4869ad546922d2f2b0b7bd9ad25c0d82df1e639c8310a5e66110d7334177ce978c248691e38f46157dc1191f44cfa4166d9d");
        nDefaultPort = 32701;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Dachcoin: 1 day
        nTargetSpacing = 1 * 60;  // Dachcoin: 1 minute
        nLastPOWBlock = 20100;
        nMaturity = 30;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 38000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1535274001;
        genesis.nNonce = 3462091;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000006a645f816b89fe77f540d65ebea9d37aa35da8690f588395d05fbd9435f"));

        vFixedSeeds.clear();
        vSeeds.clear();

        // Testnet Dachcoin addresses start with 't'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 127);
        // Testnet Dachcoin script addresses start with '5' or '6'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 12);
        // Testnet private keys start with 'n'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 113);
        // Testnet Dachcoin BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Dachcoin BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet Dachcoin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04f5a781f68716efa05231d8da248f3e8107bb24bb6a1f1c119894a912af9fad0f9ed6a2fa773e1f80b390a07c244fe8c19dce8c6d87303498388f976b5fd65b59";
        strMasternodePoolDummyAddress = "DEKDMyd3vzWzzDaz3SQ1jTP4kxWFfPiGh7";
        nStartMasternodePayments = genesis.nTime + 14400; // 4 hours after genesis
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0xb1;
        pchMessageStart[3] = 0xc4;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Dachcoin: 1 day
        nTargetSpacing = 1 * 60;        // Dachcoin: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1535274002;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1503802;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 49113;
        assert(hashGenesisBlock == uint256("0x0000008045bd20aed2df810b292e36f495b4b5bfe6b33e4a9a5e1b747164fc4b"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 34701;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
