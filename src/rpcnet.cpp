// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "rpcserver.h"

#include "main.h"
#include "net.h"
#include "netbase.h"
#include "protocol.h"
#include "sync.h"
#include "util.h"

#include <boost/foreach.hpp>
#include "json/json_spirit_value.h"

json_spirit::Value getconnectioncount(const json_spirit::Array& params, bool fHelp)
{
    if (fHelp || params.size() != 0)
        throw std::runtime_error(
            "getconnectioncount\n"
            "\nReturns the number of connections to other nodes.\n"
            "\nbResult:\n"
            "n          (numeric) The connection count\n"
            "\nExamples:\n"
            + HelpExampleCli("getconnectioncount", "")
            + HelpExampleRpc("getconnectioncount", "")
        );

    LOCK(cs_vNodes);
    return (int)vNodes.size();
}

json_spirit::Value ping(const json_spirit::Array& params, bool fHelp)
{
    if (fHelp || params.size() != 0)
        throw std::runtime_error(
            "ping\n"
            "\nRequests that a ping be sent to all other nodes, to measure ping time.\n"
            "Results provided in getpeerinfo, pingtime and pingwait fields are decimal seconds.\n"
            "Ping command is handled in queue with all other commands, so it measures processing backlog, not just network ping.\n"
            "\nExamples:\n"
            + HelpExampleCli("ping", "")
            + HelpExampleRpc("ping", "")
        );

    // Request that each node send a ping during next message processing pass
    LOCK(cs_vNodes);
    BOOST_FOREACH(CNode* pNode, vNodes) {
        pNode->fPingQueued = true;
    }

    return json_spirit::Value::null;
}

static void CopyNodeStats(std::vector<CNodeStats>& vstats)
{
    vstats.clear();

    LOCK(cs_vNodes);
    vstats.reserve(vNodes.size());
    BOOST_FOREACH(CNode* pnode, vNodes) {
        CNodeStats stats;
        pnode->copyStats(stats);
        vstats.push_back(stats);
    }
}

json_spirit::Value getpeerinfo(const json_spirit::Array& params, bool fHelp)
{
    if (fHelp || params.size() != 0)
        throw std::runtime_error(
            "getpeerinfo\n"
            "\nReturns data about each connected network node as a json array of objects.\n"
            "\nbResult:\n"
            "[\n"
            "  {\n"
            "    \"addr\":\"host:port\",      (string) The ip address and port of the peer\n"
            "    \"addrlocal\":\"ip:port\",   (string) local address\n"
            "    \"services\":\"00000001\",   (string) The services\n"
            "    \"lastsend\": ttt,           (numeric) The time in seconds since epoch (Jan 1 1970 GMT) of the last send\n"
            "    \"lastrecv\": ttt,           (numeric) The time in seconds since epoch (Jan 1 1970 GMT) of the last receive\n"
            "    \"bytessent\": n,            (numeric) The total bytes sent\n"
            "    \"bytesrecv\": n,            (numeric) The total bytes received\n"
            "    \"conntime\": ttt,           (numeric) The connection time in seconds since epoch (Jan 1 1970 GMT)\n"
            "    \"pingtime\": n,             (numeric) ping time\n"
            "    \"pingwait\": n,             (numeric) ping wait\n"
            "    \"version\": v,              (numeric) The peer version, such as 7001\n"
            "    \"subver\": \"/Satoshi:0.8.5/\",  (string) The string version\n"
            "    \"inbound\": true|false,     (boolean) Inbound (true) or Outbound (false)\n"
            "    \"startingheight\": n,       (numeric) The starting height (block) of the peer\n"
            "    \"banscore\": n,              (numeric) The ban score (stats.nMisbehavior)\n"
            "    \"syncnode\" : true|false     (booleamn) if sync node\n"
            "  }\n"
            "  ,...\n"
            "}\n"

            "\nExamples:\n"
            + HelpExampleCli("getpeerinfo", "")
            + HelpExampleRpc("getpeerinfo", "")
        );

    std::vector<CNodeStats> vstats;
    CopyNodeStats(vstats);

    json_spirit::Array ret;

    BOOST_FOREACH(const CNodeStats& stats, vstats) {
        json_spirit::Object obj;
        CNodeStateStats statestats;
        bool fStateStats = GetNodeStateStats(stats.nodeid, statestats);
        obj.push_back(json_spirit::Pair("addr", stats.addrName));
        if (!(stats.addrLocal.empty()))
            obj.push_back(json_spirit::Pair("addrlocal", stats.addrLocal));
        obj.push_back(json_spirit::Pair("services", strprintf("%08x", stats.nServices)));
        obj.push_back(json_spirit::Pair("lastsend", stats.nLastSend));
        obj.push_back(json_spirit::Pair("lastrecv", stats.nLastRecv));
        obj.push_back(json_spirit::Pair("bytessent", stats.nSendBytes));
        obj.push_back(json_spirit::Pair("bytesrecv", stats.nRecvBytes));
        obj.push_back(json_spirit::Pair("conntime", stats.nTimeConnected));
        obj.push_back(json_spirit::Pair("pingtime", stats.dPingTime));
        if (stats.dPingWait > 0.0)
            obj.push_back(json_spirit::Pair("pingwait", stats.dPingWait));
        obj.push_back(json_spirit::Pair("version", stats.nVersion));
        // Use the sanitized form of subver here, to avoid tricksy remote peers from
        // corrupting or modifiying the JSON output by putting special characters in
        // their ver message.
        obj.push_back(json_spirit::Pair("subver", stats.cleanSubVer));
        obj.push_back(json_spirit::Pair("inbound", stats.fInbound));
        obj.push_back(json_spirit::Pair("startingheight", stats.nStartingHeight));
        if (fStateStats) {
            obj.push_back(json_spirit::Pair("banscore", statestats.nMisbehavior));
        }
        obj.push_back(json_spirit::Pair("syncnode", stats.fSyncNode));

        ret.push_back(obj);
    }

    return ret;
}

json_spirit::Value addnode(const json_spirit::Array& params, bool fHelp)
{
    std::string strCommand;
    if (params.size() == 2)
        strCommand = params[1].get_str();
    if (fHelp || params.size() != 2 ||
        (strCommand != "onetry" && strCommand != "add" && strCommand != "remove"))
        throw std::runtime_error(
            "addnode \"node\" \"add|remove|onetry\"\n"
            "\nAttempts add or remove a node from the addnode list.\n"
            "Or try a connection to a node once.\n"
            "\nArguments:\n"
            "1. \"node\"     (string, required) The node (see getpeerinfo for nodes)\n"
            "2. \"command\"  (string, required) 'add' to add a node to the list, 'remove' to remove a node from the list, 'onetry' to try a connection to the node once\n"
            "\nExamples:\n"
            + HelpExampleCli("addnode", "\"192.168.0.6:12340\" \"onetry\"")
            + HelpExampleRpc("addnode", "\"192.168.0.6:12340\", \"onetry\"")
        );

    std::string strNode = params[0].get_str();

    if (strCommand == "onetry")
    {
        CAddress addr;
        ConnectNode(addr, strNode.c_str());
        return json_spirit::Value::null;
    }

    LOCK(cs_vAddedNodes);
    std::vector<std::string>::iterator it = vAddedNodes.begin();
    for(; it != vAddedNodes.end(); it++)
        if (strNode == *it)
            break;

    if (strCommand == "add")
    {
        if (it != vAddedNodes.end())
            throw JSONRPCError(RPC_CLIENT_NODE_ALREADY_ADDED, "Error: Node already added");
        vAddedNodes.push_back(strNode);
    }
    else if(strCommand == "remove")
    {
        if (it == vAddedNodes.end())
            throw JSONRPCError(RPC_CLIENT_NODE_NOT_ADDED, "Error: Node has not been added.");
        vAddedNodes.erase(it);
    }

    return json_spirit::Value::null;
}

json_spirit::Value getaddednodeinfo(const json_spirit::Array& params, bool fHelp)
{
    if (fHelp || params.size() < 1 || params.size() > 2)
        throw std::runtime_error(
            "getaddednodeinfo dns ( \"node\" )\n"
            "\nReturns information about the given added node, or all added nodes\n"
            "(note that onetry addnodes are not listed here)\n"
            "If dns is false, only a list of added nodes will be provided,\n"
            "otherwise connected information will also be available.\n"
            "\nArguments:\n"
            "1. dns        (boolean, required) If false, only a list of added nodes will be provided, otherwise connected information will also be available.\n"
            "2. \"node\"   (string, optional) If provided, return information about this specific node, otherwise all nodes are returned.\n"
            "\nResult:\n"
            "[\n"
            "  {\n"
            "    \"addednode\" : \"192.168.0.201\",   (string) The node ip address\n"
            "    \"connected\" : true|false,          (boolean) If connected\n"
            "    \"addresses\" : [\n"
            "       {\n"
            "         \"address\" : \"192.168.0.201:12340\",  (string) The auroracoin server host and port\n"
            "         \"connected\" : \"outbound\"           (string) connection, inbound or outbound\n"
            "       }\n"
            "       ,...\n"
            "     ]\n"
            "  }\n"
            "  ,...\n"
            "]\n"
            "\nExamples:\n"
            + HelpExampleCli("getaddednodeinfo", "true")
            + HelpExampleCli("getaddednodeinfo", "true \"192.168.0.201\"")
            + HelpExampleRpc("getaddednodeinfo", "true, \"192.168.0.201\"")
        );

    bool fDns = params[0].get_bool();

    std::list<std::string> laddedNodes(0);
    if (params.size() == 1)
    {
        LOCK(cs_vAddedNodes);
        BOOST_FOREACH(std::string& strAddNode, vAddedNodes)
            laddedNodes.push_back(strAddNode);
    }
    else
    {
        std::string strNode = params[1].get_str();
        LOCK(cs_vAddedNodes);
        BOOST_FOREACH(std::string& strAddNode, vAddedNodes)
            if (strAddNode == strNode)
            {
                laddedNodes.push_back(strAddNode);
                break;
            }
        if (laddedNodes.size() == 0)
            throw JSONRPCError(RPC_CLIENT_NODE_NOT_ADDED, "Error: Node has not been added.");
    }

    json_spirit::Array ret;
    if (!fDns)
    {
        BOOST_FOREACH(std::string& strAddNode, laddedNodes)
        {
            json_spirit::Object obj;
            obj.push_back(json_spirit::Pair("addednode", strAddNode));
            ret.push_back(obj);
        }
        return ret;
    }

    std::list<std::pair<std::string, std::vector<CService> > > laddedAddreses(0);
    BOOST_FOREACH(std::string& strAddNode, laddedNodes)
    {
        std::vector<CService> vservNode(0);
        if(Lookup(strAddNode.c_str(), vservNode, Params().GetDefaultPort(), fNameLookup, 0))
            laddedAddreses.push_back(std::make_pair(strAddNode, vservNode));
        else
        {
            json_spirit::Object obj;
            obj.push_back(json_spirit::Pair("addednode", strAddNode));
            obj.push_back(json_spirit::Pair("connected", false));
            json_spirit::Array addresses;
            obj.push_back(json_spirit::Pair("addresses", addresses));
        }
    }

    LOCK(cs_vNodes);
    for (std::list<std::pair<std::string, std::vector<CService> > >::iterator it = laddedAddreses.begin(); it != laddedAddreses.end(); it++)
    {
        json_spirit::Object obj;
        obj.push_back(json_spirit::Pair("addednode", it->first));

        json_spirit::Array addresses;
        bool fConnected = false;
        BOOST_FOREACH(CService& addrNode, it->second)
        {
            bool fFound = false;
            json_spirit::Object node;
            node.push_back(json_spirit::Pair("address", addrNode.ToString()));
            BOOST_FOREACH(CNode* pnode, vNodes)
                if (pnode->addr == addrNode)
                {
                    fFound = true;
                    fConnected = true;
                    node.push_back(json_spirit::Pair("connected", pnode->fInbound ? "inbound" : "outbound"));
                    break;
                }
            if (!fFound)
                node.push_back(json_spirit::Pair("connected", "false"));
            addresses.push_back(node);
        }
        obj.push_back(json_spirit::Pair("connected", fConnected));
        obj.push_back(json_spirit::Pair("addresses", addresses));
        ret.push_back(obj);
    }

    return ret;
}

json_spirit::Value getnettotals(const json_spirit::Array& params, bool fHelp)
{
    if (fHelp || params.size() > 0)
        throw std::runtime_error(
            "getnettotals\n"
            "\nReturns information about network traffic, including bytes in, bytes out,\n"
            "and current time.\n"
            "\nResult:\n"
            "{\n"
            "  \"totalbytesrecv\": n,   (numeric) Total bytes received\n"
            "  \"totalbytessent\": n,   (numeric) Total bytes sent\n"
            "  \"timemillis\": t        (numeric) Total cpu time\n"
            "}\n"
            "\nExamples:\n"
            + HelpExampleCli("getnettotals", "")
            + HelpExampleRpc("getnettotals", "")
       );

    json_spirit::Object obj;
    obj.push_back(json_spirit::Pair("totalbytesrecv", CNode::GetTotalBytesRecv()));
    obj.push_back(json_spirit::Pair("totalbytessent", CNode::GetTotalBytesSent()));
    obj.push_back(json_spirit::Pair("timemillis", GetTimeMillis()));
    return obj;
}

json_spirit::Value getnetworkinfo(const json_spirit::Array& params, bool fHelp)
{
    if (fHelp || params.size() != 0)
        throw std::runtime_error(
            "getnetworkinfo\n"
            "Returns an object containing various state info regarding P2P networking.\n"
            "\nResult:\n"
            "{\n"
            "  \"version\": xxxxx,           (numeric) the server version\n"
            "  \"protocolversion\": xxxxx,   (numeric) the protocol version\n"
            "  \"timeoffset\": xxxxx,        (numeric) the time offset\n"
            "  \"connections\": xxxxx,       (numeric) the number of connections\n"
            "  \"proxy\": \"host:port\",     (string, optional) the proxy used by the server\n"
            "  \"relayfee\": x.xxxx,         (numeric) minimum relay fee for non-free transactions in btc/kb\n"
            "  \"localaddresses\": [,        (array) list of local addresses\n"
            "    \"address\": \"xxxx\",      (string) network address\n"
            "    \"port\": xxx,              (numeric) network port\n"
            "    \"score\": xxx              (numeric) relative score\n"
            "  ]\n"
            "}\n"
            "\nExamples:\n"
            + HelpExampleCli("getnetworkinfo", "")
            + HelpExampleRpc("getnetworkinfo", "")
        );

    proxyType proxy;
    GetProxy(NET_IPV4, proxy);

    json_spirit::Object obj;
    obj.push_back(json_spirit::Pair("version",       (int)CLIENT_VERSION));
    obj.push_back(json_spirit::Pair("protocolversion",(int)PROTOCOL_VERSION));
    obj.push_back(json_spirit::Pair("timeoffset",    GetTimeOffset()));
    obj.push_back(json_spirit::Pair("connections",   (int)vNodes.size()));
    obj.push_back(json_spirit::Pair("proxy",         (proxy.first.IsValid() ? proxy.first.ToStringIPPort() : std::string())));
    obj.push_back(json_spirit::Pair("relayfee",      ValueFromAmount(CTransaction::nMinRelayTxFee)));
    json_spirit::Array localAddresses;
    {
        LOCK(cs_mapLocalHost);
        BOOST_FOREACH(const PAIRTYPE(CNetAddr, LocalServiceInfo) &item, mapLocalHost)
        {
            json_spirit::Object rec;
            rec.push_back(json_spirit::Pair("address", item.first.ToString()));
            rec.push_back(json_spirit::Pair("port", item.second.nPort));
            rec.push_back(json_spirit::Pair("score", item.second.nScore));
            localAddresses.push_back(rec);
        }
    }
    obj.push_back(json_spirit::Pair("localaddresses", localAddresses));
    return obj;
}
