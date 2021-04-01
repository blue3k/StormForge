﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : Kyungkun Ko
//
// Description : Network policy builder
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;
using ProtocolXml;

namespace ProtocolCompiler
{
    class MessageNetPolicyBuilder : CppBuilder
    { 
        // constructor
        public MessageNetPolicyBuilder(string strBasePath)
            : base(strBasePath + "Lib/Protocol/Policy")
        {
        }

        public virtual string OutputHeaderName()
        {
            return Group.Name + "NetPolicy.h";
        }

        public virtual string OutputCPPName()
        {
            return Group.Name + "NetPolicy.cpp";
        }

        public virtual string MessageClassHeaderName { get { return Group.Name + "MsgClass.h"; } }

        public virtual string SvrPolicyClassName { get { return "NetSvrPolicy" + Group.Name; } }


        protected virtual void BuildHPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// CopyRight (c) The Braves");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine(string.Format("// Description : {0} Message debug definitions", Group.Name));
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("#pragma once");
            OutStream.WriteLine("");
            OutStream.WriteLine("#include \"SFTypedefs.h\"");
            OutStream.WriteLine("#include \"Protocol/SFProtocol.h\"");
            OutStream.WriteLine("#include \"Net/SFNetDef.h\"");
            NewLine(3);


            // namespace definition
            OpenSection("namespace", PrjPrefix);

            OutStream.WriteLine("   class MessageEndpoint;");
            OutStream.WriteLine("   class VariableTable;");
            OutStream.WriteLine("   struct ActorMovement;");

            NewLine(2);
        }


        void BuildCPPPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// CopyRight (c) The Braves");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine(string.Format("// Description : {0} Message debug implementations", Group.Name));
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("");
            OutStream.WriteLine(string.Format("#include \"{0}\"", PreCompiledHeader));
            OutStream.WriteLine("#include \"SFTypedefs.h\"");
            OutStream.WriteLine("#include \"Net/SFNetDef.h\"");
            OutStream.WriteLine("#include \"Net/SFMessage.h\"");
            OutStream.WriteLine("#include \"Net/SFMessageEndpoint.h\"");
            OutStream.WriteLine("#include \"Actor/Movement/SFActorMovement.h\"");
            if (Group.IsServer)
                OutStream.WriteLine("#include \"Protocol/SvrProtocol.h\"");
            OutStream.WriteLine(string.Format("#include \"Protocol/{0}\"", OutputHeaderName()));
            OutStream.WriteLine(string.Format("#include \"Protocol/{0}\"", MessageClassHeaderName));
            if (Group.IsServer)
                OutStream.WriteLine("#include \"ProtocolTrace.h\"");
            
            
            NewLine(3);

            // namespace definition
            OpenSection("namespace", PrjPrefix);
        }

        public override string ParamInString(Parameter[] parameter, bool bUseOriginalType = false)
        {
            string strParams = "";

            if (parameter == null)
                return strParams;

            string Separator = "";
            foreach (Parameter param in parameter)
            {
                strParams += Separator;
                Separator = ", ";

                if (param.IsArray) // array
                {
                    strParams += string.Format("const {0}& {1}", InArrayTypeName(param), InParamName(param.Name));
                }
                else if (IsStrType(param)) // string type
                {
                    strParams += string.Format("const {0} {1}", StrTypeString(param), InParamName(param.Name));
                }
                else // generic type
                {
                    strParams += string.Format("const {0} &{1}", ToTargetTypeName(param.Type), InParamName(param.Name));
                }
            }

            return strParams;
        }

        protected virtual void BuildServerPolicyH()
        {
            Parameter[] newparams;

            OpenSection("class", string.Format("{0}", SvrPolicyClassName));
            MatchIndent(); OutStream.WriteLine("private:");
            MatchIndent(1); OutStream.WriteLine("SharedPointerT<MessageEndpoint> m_Endpoint;");
            MatchIndent(); OutStream.WriteLine("public:");
            MatchIndent(); OutStream.WriteLine("// Constructor");
            MatchIndent(); OutStream.WriteLine(
                string.Format("{0} ( const SharedPointerT<MessageEndpoint>& pEndpoint ) : m_Endpoint(pEndpoint)", SvrPolicyClassName));
            MatchIndent(); OutStream.WriteLine("{}");
            NewLine();

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Res, msg.Res);
                    MatchIndent(); OutStream.WriteLine(
                        string.Format("Result {0}Res( {1} );", msg.Name, ParamInString(newparams)));
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// S2C: " + baseMsg.Desc);
                    ProtocolsProtocolGroupS2CEvent msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    MatchIndent(); OutStream.WriteLine(
                        string.Format("Result {0}S2CEvt( {1} );", msg.Name, ParamInString(newparams)));
                }
            }

            NewLine();

            CloseSection();
        }

        void BuildIClientPolicyH()
        {
            Parameter[] newparams;

            OpenSection("class", string.Format("{0} ", PolicyClassName));
            MatchIndent(); OutStream.WriteLine("private:");
            MatchIndent(1); OutStream.WriteLine("SharedPointerT<MessageEndpoint> m_Endpoint;");
            MatchIndent(); OutStream.WriteLine("public:");
            MatchIndent(); OutStream.WriteLine("// Constructor");
            MatchIndent(); OutStream.WriteLine(
                string.Format("{0} (const SharedPointerT<MessageEndpoint>& pEndpoint ) : m_Endpoint(pEndpoint)", PolicyClassName));
            MatchIndent(); OutStream.WriteLine("{}");
            NewLine();

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Cmd, msg.Cmd);
                    MatchIndent(); OutStream.WriteLine(
                        string.Format("Result {0}Cmd( {1} );", msg.Name, ParamInString(newparams)));
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    MatchIndent(); OutStream.WriteLine(
                        string.Format("Result {0}C2SEvt( {1} );", msg.Name, ParamInString(newparams)));
                }
            }

            NewLine();

            CloseSection();
        }

        // Build parser class implementation
        void BuildNetPolicyClassParserImpl( string Name, string typeName, Parameter[] parameters)
        {
            if((typeName == "Cmd") || (typeName == "C2SEvt"))
                OpenSection("Result", string.Format("{0}::{1}{2}( {3} )", PolicyClassName, Name, typeName, ParamInString(parameters)));
            else
                OpenSection("Result", string.Format("{0}::{1}{2}( {3} )", SvrPolicyClassName, Name, typeName, ParamInString(parameters)));
            
            DefaultHRESULT(); NewLine();

            MatchIndent(); OutStream.WriteLine(" MessageDataPtr pMessage;");
            MatchIndent(); OutStream.WriteLine(" protocolCheckPtr(m_Endpoint);");
            NewLine();

            if (parameters != null && parameters.Length > 0)
            {
                MatchIndent(); OutStream.WriteLine(" pMessage = SF::Message::{0}::{1}{2}::Create(GetSystemHeap(), {3});", Group.Name, Name, typeName, ParamArgument(parameters));
            }
            else
            {
                MatchIndent(); OutStream.WriteLine(" pMessage = SF::Message::{0}::{1}{2}::Create(GetSystemHeap());", Group.Name, Name, typeName);
            }

            MatchIndent(); OutStream.WriteLine(" protocolCheckPtr(*pMessage);");
            NewLine();

            MatchIndent(); OutStream.WriteLine(" return m_Endpoint->Send( pMessage );");
            NewLine();
            
            ReturnHR(); NewLine();

            CloseSection();
        }

        void BuildSvrPolicyCPP()
        {
            Parameter[] newparams;

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Res, msg.Res);
                    BuildNetPolicyClassParserImpl(msg.Name, "Res", newparams);
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// S2C: " + baseMsg.Desc);
                    ProtocolsProtocolGroupS2CEvent msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildNetPolicyClassParserImpl(msg.Name, "S2CEvt", newparams);
                }
            }

        }

        void BuildClientPolicyCPP()
        {
            Parameter[] newparams;

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Cmd, msg.Cmd);
                    BuildNetPolicyClassParserImpl(msg.Name, "Cmd", newparams);
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildNetPolicyClassParserImpl(msg.Name, "C2SEvt", newparams);
                }
            }
        }

        void BuildH()
        {
            // build IParser
            OpenOutFile(OutputHeaderName());

            BuildHPrefix();

            BuildIClientPolicyH();
            NewLine(2);

            BuildServerPolicyH();
            NewLine(2);

            CloseOutFile();
        }

        void BuildCPP()
        {
            OpenOutFile(OutputCPPName());

            BuildCPPPrefix();

            BuildClientPolicyCPP();
            NewLine(2);

            BuildSvrPolicyCPP();
            NewLine(2);

            CloseOutFile();
        }

        public override void Build()
        {
            BuildH();
            BuildCPP();
        }

    }
}
