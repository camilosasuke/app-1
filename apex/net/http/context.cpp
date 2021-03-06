#include "framework.h"
#include "apex/net/sockets/_sockets.h"
#include "apex/const/idpool.h"
#include "apex/astr.h"
#include <time.h>


#define DEBUG_LEVEL_SICK 9
#define DEBUG_LEVEL_NORMAL 4
#define HTTP_DEBUG_LEVEL DEBUG_LEVEL_NORMAL


namespace http
{


   context::context()
   {

      m_setHttp["max_http_post"] = 5 * 1024 * 1024; // 5MB;

      value("dw")= ::millis::now();

      m_pmutexPac = nullptr;
      m_pmutexProxy = nullptr;
      m_pmutexDownload = nullptr;

   }


   context::~context()
   {

   }


   void context::http_application_destruct()
   {

      message_receiver_destruct();

   }


   property_set & context::process_set(property_set & set, const char * pszUrl)
   {

      set["app"] = get_context_application();

      string strServer = System.url().get_root(pszUrl);

      if (strServer == "server.ca2.cc")
      {

         set["raw_http"] = true;

      }
      else if (!strServer.ends_ci("ca2.cc") && strServer != "ca2.cc")
      {

         set["raw_http"] = true;

      }

      return set;

   }


   bool context::get(::sockets::socket_handler & handler, __pointer(::sockets::http_client_socket) & psession, const char * pszUrl, property_set & set)
   {

      return http_get(handler, psession, pszUrl, process_set(set, pszUrl));

   }


   estatus context::get(memory_base * pmemory, const char * pszUrl, property_set & set)
   {

      set["get_memory"] = pmemory;

      auto estatus = _get(pszUrl, process_set(set, pszUrl));

      set.remove_by_name("get_memory");

      return estatus;

   }


   string context::api_get(const char * pszUrl, property_set & set)
   {

      ::file::path url("https://api.ca2.cc/");

      url /= pszUrl;

      return get(url, set);

   }


   string context::api_get(const char * pszUrl)
   {

      property_set set;

      set["disable_common_name_cert_check"] = true;

      return api_get(pszUrl, set);

   }


   estatus context::_get(const char * pszUrl, property_set & set)
   {

      ::http::message message;

      message.m_pset = &set;

      message.m_strUrl = pszUrl;

      get(&message);

      return set["get_estatus"].estatus();

   }


   payload context::get(const char * pszUrl, property_set & set)
   {

      set["get_response"] = ""; // create get_response field

      auto estatus = _get(pszUrl, set);

      if (!estatus)
      {

         return estatus;

      }

      return set["get_response"].get_string();

   }


   estatus context::get(string & str, const char * pszUrl, property_set & set)
   {

      set["get_response"] = "";

      set["bool_result"] = get(pszUrl, process_set(set, pszUrl));

      str = set["get_response"].get_string();

      return set["get_status"].estatus();

   }


   bool context::is_file_or_dir(const char * pszUrl, payload * pvarQuery, ::file::enum_type * petype, property_set & set)
   {

      string strUrl(pszUrl);

      string strFile(strUrl);

      strFile.replace(":", "_");
      strFile.replace("//", "/");
      strFile.replace("?", "%19");
      strFile = Context.dir().cache() / strFile + ".meta_information";

      string strCache;

      if (!set["nocache"].get_bool())
      {

         Context.file().as_string(strFile);

         if (strCache.has_char())
         {

            if (strCache == "file")
            {

               if (::is_set(petype))
               {

                  *petype = ::file::type_file;

               }

               return true;

            }
            else if (strCache == "folder")
            {

               if (::is_set(petype))
               {

                  *petype = ::file::type_folder;

               }

               return true;

            }
            else if (strCache == "matter")
            {

               if (::is_set(petype))
               {

                  *petype = ::file::type_element;

               }

               return true;

            }
            else if (strCache == "itdoesntexist")
            {

               if (::is_set(petype))
               {

                  *petype = ::file::type_none;

               }

               return false;

            }

         }

      }

      if (::str::find_wwci("ca2", System.url().get_server(pszUrl)) < 0 && System.url().get_object(pszUrl).find_ci("/matter/") < 0)
      {

         set["raw_http"] = true;

      }

      ::file::enum_type etype = ::file::type_none;

      bool bExists = is_file_or_dir(strUrl, process_set(set, pszUrl), &etype);

      if (bExists)
      {

         if (etype == ::file::type_folder)
         {

            strCache = "folder";

         }
         else if (etype == ::file::type_file)
         {

            strCache = "file";

         }
         else if (etype == ::file::type_element)
         {

            strCache = "matter";

         }
         else
         {

            strCache = "itdoesntexist";

         }

      }
      else
      {

         strCache = "itdoesntexist";

      }

      Context.file().put_contents(strFile, strCache);

      if (::is_set(petype))
      {

         *petype = etype;

      }

      return bExists;

   }


   //payload context::length(const char * pszUrl, property_set & set)
   //{

   //   return length(pszUrl, nullptr, set);

   //}


   payload context::length(const char * pszUrl, payload * pvarQuery, property_set & set)
   {

      string strUrl(pszUrl);

      string strFile(strUrl);

      strFile.replace(":", "_");
      strFile.replace("//", "/");
      strFile.replace("?", "%19");
      strFile = Context.dir().cache() / strFile + ".length_question";

      bool bNoCache = set["nocache"].get_bool();

      string strCache;

      if (!bNoCache)
      {

         strCache = Context.file().as_string(strFile);

         if (strCache.has_char())
         {

            if (strCache == "-1")
            {

               return -1;

            }
            else if (strCache == "no")
            {

               return ::str::to_i64(strCache);

            }

         }

      }

      payload len = length(strUrl, process_set(set, pszUrl));

      if (len.is_empty())
      {

         strCache = "-1";

      }
      else
      {

         strCache = __str(len.i64());

      }

      Context.file().put_contents(strFile, strCache);

      return len;

   }


   //bool context::request(const char * pszRequest, const char * pszUrl, property_set & set)
   //{

   //   return request(pszRequest, pszUrl, process_set(set, pszUrl));

   //}


   //bool context::download(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession, const char * pszUrl, payload varFile, property_set & set)
   //{

   //   return download(handler, psession, pszUrl, varFile, process_set(set, pszUrl));

   //}


 /*  bool context::download(const char * pszUrl, payload varFile, property_set & set)
   {
      return download(pszUrl, varFile, process_set(set, pszUrl));
   }*/

   bool context::put(const char * pszUrl, memory_base * pmemory, property_set & set)
   {

      return put(pszUrl, *pmemory, process_set(set, pszUrl));
   }

   //bool context::put(const char * pszUrl, file_pointer  pfile, property_set & set)
   //{
   //   return put(pszUrl, pfile, process_set(set, pszUrl));
   //}



   string context::locale_schema_url(const char * pszUrl, const char * pszLocale, const char * pszSchema)
   {

      string str;

      //      i32 iAttempt = 0;

      string strUrl(pszUrl);

      if (strUrl.find("?") >= 0)
      {

         strUrl += "&";

      }
      else
      {

         strUrl += "?";

      }

      strUrl += "lang=" + string(pszLocale) + "&styl=" + string(pszSchema);

      return strUrl;

   }


   string context::get_locale_schema(const char * pszUrl, const char * pszLocale, const char * pszSchema)
   {

      Application.message_box("What?!" + e_message_box_ok);

      string strUrl = locale_schema_url(pszUrl, pszLocale, pszSchema);

      string str;

      //      int iAttempt = 0;
      //
      //      property_set set;
      //
      //      __pointer(::sockets::http_session) psession;
      //
      //      string strFontopusServer;
      //
      //      if(atoi(System.url().get_param(pszUrl, "authnone")) == 1
      //            || System.url().get_param(pszUrl,"sessid").compare_ci("noauth") == 0)
      //      {
      //
      //         strFontopusServer = pszUrl;
      //
      //      }
      //      else
      //      {
      //
      //         strFontopusServer = psession->account()->authenticator()->get_account_server(pszUrl);
      //
      //      }
      //
      //      while(::get_task() == nullptr || thread_get_run())
      //      {
      //
      //         {
      //
      //            set["get_response"] = "";
      //
      //            str = get(strUrl, set);
      //
      //            if(str.has_char())
      //               return str;
      //
      //         }
      //
      //         iAttempt++;
      //
      //         if(iAttempt > 11)
      //            return "";
      //
      //         millis_sleep(iAttempt * 840);
      //
      //      }

      return str;

   }






   //context::~context()
   //{

   //}


   void context::http_system_destruct()
   {

      message_receiver_destruct();

   }


   i32 context::auto_config_proxy_count()
   {

      return 4;

   }


   void context::auto_config_proxy(i32 i)
   {

      return;
      //      if(i == 0)
      //      {
      //      }
      //      else if(i == 1)
      //      {
      //         // telmico: no proxy
      //         string str = Context.file().as_string(Context.dir().appdata() / "machine/proxy.xml");
      //         if(str.has_char() && str.find("<") >= 0 && str.find(">") > 0)
      //         {
      //            Context.file().copy(Context.dir().appdata()/ "proxy_original.xml", Context.dir().install()/ "proxy.xml", false);
      //         }
      //         if(Context.file().exists(Context.dir().appdata()/ "proxy.xml"))
      //         {
      //            try
      //            {
      //               Context.file().del(Context.dir().appdata()/ "proxy.xml");
      //            }
      //            catch(...)
      //            {
      //            }
      //         }
      //      }
      //      else if(i == 2)
      //      {
      //         // telmico: original proxy configuration
      //         if(Context.file().exists(Context.dir().appdata()/ "proxy_original.xml"))
      //         {
      //            Context.file().copy(Context.dir().appdata()/ "proxy.xml", Context.dir().appdata()/"proxy_original.xml", false);
      //         }
      //      }
      //      else
      //      {
      //         // telmico: simple default proxy configuration : hostname=>proxy - try etc/hosts port=>80  - assume HTTP proxy
      //         string str = Context.file().as_string(Context.dir().appdata()/"proxy.xml");
      //         if(str.has_char() && str.find("<") >= 0 && str.find(">") > 0)
      //         {
      //            Context.file().copy(Context.dir().appdata()/"proxy_original.xml", Context.dir().appdata()/"proxy.xml", false);
      //         }
      //         Context.file().put_contents(Context.dir().appdata()/"proxy.xml", "proxy");
      //      }
   }


   void context::defer_auto_initialize_proxy_configuration()
   {

      string strHost = Context.file().as_string(Context.dir().appdata() / "database\\text\\last_good_known_account_com.txt");

      string_array straRequestingServer;

      straRequestingServer.add("ca2.cc");

      if (!straRequestingServer.contains_ci(strHost))
      {

         strHost = "ca2.cc";

      }

      straRequestingServer.remove(strHost);

      straRequestingServer.insert_at(0, strHost);

      bool bOk = false;

      if (bOk)
      {

         return;

      }

      auto_config_proxy(0);

   }

   context::pac::pac(::layered * pobjectContext) :
      ::object(pobjectContext)
   {

      __throw(todo("scripting"));
      //m_pjs = new tinyjs();

   }

   context::pac::~pac()
   {

      //__throw(todo("scripting"));


      //if (m_pjs == nullptr)
      //{

      //   delete m_pjs;

      //}

   }


   context::pac * context::get_pac(const char * pszUrl)
   {

      single_lock sl(m_pmutexPac, true);

      auto ppair = m_mapPac.plookup(pszUrl);

      if (ppair == nullptr || (ppair->element2()->m_millisLastChecked.elapsed()) > (84 * 1000))
      {
         if (ppair != nullptr)
         {
            //            delete ppair->element2();
            m_mapPac.remove_key(pszUrl);
         }

         auto ppac = __new(class pac(get_context_object()));

         ppac->m_millisLastChecked= ::millis::now();

         ppac->m_strUrl = pszUrl;

         payload varFile;

         varFile["url"] = ppac->m_strUrl;
         varFile["disable_ca2_sessid"] = true;
         varFile["no_proxy_config"] = true;

         ppac->m_strAutoConfigScript = Context.file().as_string(varFile);


         m_mapPac.set_at(pszUrl, ppac);

         if (ppac->m_strAutoConfigScript.is_empty())
         {
            return nullptr;
         }

         //__throw(todo("scripting"));
         //registerFunctions(ppac->m_pjs);
         //registerJavascriptFunctions(ppac->m_pjs);
         //ppac->m_pjs->execute(ppac->m_strAutoConfigScript);

         ppair = m_mapPac.plookup(pszUrl);

         if (ppair == nullptr)
            return nullptr;
      }

      if (ppair->element2()->m_strAutoConfigScript.is_empty())
      {

         return nullptr;

      }

      return ppair->element2();

   }


   context::proxy::proxy(::layered * pobjectContext) :
      ::object(pobjectContext)
   {

      m_bDirect = true;

   }


   ::http::context::proxy * context::get_proxy(const char * pszUrl)
   {

      single_lock sl(m_pmutexProxy, true);

      auto ppair = m_mapProxy.plookup(pszUrl);

      if (ppair == nullptr || (ppair->element2()->m_millisLastChecked.elapsed()) > (84 * 1000))
      {
         if (ppair != nullptr)
         {
            //            delete ppair->element2();
            m_mapPac.remove_key(pszUrl);
         }

         auto pproxy = __new(class ::http::context::proxy(get_context_object()));

         pproxy->m_millisLastChecked= ::millis::now();

         pproxy->m_strUrl = pszUrl;

         config_proxy(pszUrl, pproxy);

         m_mapProxy.set_at(pszUrl, pproxy);

         return pproxy;

      }

      return ppair->element2();

   }


   bool context::try_pac_script(const char * pszScriptUrl, const char * pszUrl, proxy * pproxy)
   {

      single_lock sl(m_pmutexPac, true);

      string strProxyServer;

      string strUrl(pszScriptUrl);

      if (::str::begins(pszUrl, strUrl))
      {
         pproxy->m_bDirect = true;
         return true;
      }

      class pac * ppac = get_pac(pszScriptUrl);

      if (ppac == nullptr)
         return false;

      string strHost;

      strHost = System.url().get_server(pszUrl);

      i32 port = System.url().get_port(pszUrl);

      ::net::address ad(strHost, port);

      strHost = ad.get_display_number();

      string payload;
      //__throw(todo("scripting"));
      //try
      //{
      //   payload = ppac->m_pjs->evaluate("FindProxyForURL('" + string(pszUrl) + "', '" + strHost + "');");
      //}
      //catch (...)
      //{
      //   return false;
      //}

      if (payload.compare_ci("DIRECT") == 0)
      {

         pproxy->m_bDirect = true;

      }
      else if (::str::begins_eat_ci(payload, "PROXY"))
      {
         payload.trim();
         string_array stra;
         stra.explode(":", payload);
         pproxy->m_bDirect = false;
         pproxy->m_strProxy = stra[0];
         pproxy->m_iPort = stra.get_size() > 1 ? ::atoi(stra[1]) : 80;
      }
      else
      {
         pproxy->m_bDirect = true;
      }

      return true;

   }


   void context::config_proxy(const char * pszUrl, ::sockets::http_tunnel * psocket)
   {

#ifdef _UWP

      psocket->m_bDirect = true;

#else

      ::http::context::proxy * pproxy = get_proxy(pszUrl);

      if (pproxy == nullptr)
         return;

      if (pproxy->m_bDirect)
      {
         psocket->m_bDirect = true;
      }
      else
      {
         psocket->m_bDirect = false;
         psocket->m_strProxy = pproxy->m_strProxy;
         psocket->m_iProxyPort = pproxy->m_iPort;
      }

#endif

   }


   void context::config_proxy(const char * pszUrl, ::http::context::proxy * pproxy)
   {

      //__throw(todo("xml"));

      //xml::document doc;

      //::file::path pathProxyXml = Context.dir().appdata() / "proxy.xml";

      //if (!Context.file().exists(pathProxyXml))
      //{

      //   pproxy->m_bDirect = true;

      //   return;

      //}

      //string str = Context.file().as_string(pathProxyXml);

      //if (str.has_char() && str.find("<") < 0 && str.find(">") < 0)
      //{

      //   string_array stra;

      //   stra.explode(":", str);

      //   if (stra.get_size() > 0 && stra[0].has_char())
      //   {

      //      pproxy->m_bDirect = false;

      //      pproxy->m_strProxy = stra[0];

      //      if (stra.get_size() >= 2)
      //      {

      //         pproxy->m_iPort = atoi(stra[1]);

      //      }
      //      else
      //      {

      //         pproxy->m_iPort = 80;

      //      }

      //      return;

      //   }

      //}

      //if (!doc.load(str))
      //{

      //   pproxy->m_bDirect = true;

      //   return;

      //}

      //bool bOk = true;

      //string strHost = System.url().get_server(pszUrl);

      //i32 iHostPort = System.url().get_port(pszUrl);

      //::net::address ipHost(strHost, iHostPort);
      //for (i32 iNode = 0; iNode < doc.root()->get_children_count(); iNode++)
      //{
      //   __pointer(::xml::node) pnode = doc.root()->child_at(iNode);
      //   if (pnode->get_name() == "proxy")
      //   {

      //      ::net::address ipAddress(pnode->attribute("address").get_string(), 0);

      //      ::net::address ipMask(pnode->attribute("mask").get_string(), 0);

      //      if (ipHost.is_in_same_net(ipAddress, ipMask))
      //      {

      //         if (pnode->attribute("server") == "DIRECT")
      //         {

      //            pproxy->m_bDirect = true;

      //            return;

      //         }
      //         else
      //         {

      //            pproxy->m_bDirect = false;

      //            pproxy->m_strProxy = pnode->attribute("server");

      //            pproxy->m_iPort = pnode->attribute("port");

      //            TRACE("Select Proxy : address %s mask %s server %s port %d", pnode->attribute("address").get_string().c_str(),
      //               pnode->attribute("mask").get_string().c_str(), pproxy->m_strProxy.c_str(), pproxy->m_iPort);

      //            return;

      //         }

      //      }

      //   }

      //}

      //if (doc.attribute("server") == "DIRECT")
      //{

      //   pproxy->m_bDirect = true;

      //   return;

      //}
      //else
      //{

      //   pproxy->m_bDirect = false;
      //   pproxy->m_strProxy = doc.root()->attribute("server");
      //   pproxy->m_iPort = doc.root()->attribute("port");
      //   return;

      //}


      ////      if(!bOk)
      ////      {
      ////
      ////         //bool bAutoDetect = Context.os().connection_settings_get_auto_detect();
      ////
      ////         //if(bAutoDetect)
      ////         //{
      ////
      ////         //   TRACE("proxy auto_detect true");
      ////
      ////         //   string strUrl = Context.os().connection_settings_get_auto_config_url();
      ////
      ////         //   if(strUrl.has_char())
      ////         //   {
      ////
      ////         //      TRACE("get_auto_config_url : %s",strUrl);
      ////
      ////         //      if(try_pac_script(strUrl,pszUrl,pproxy))
      ////         //         return;
      ////
      ////         //   }
      ////
      ////         //}
      ////         //else
      ////         //{
      ////
      ////         //   TRACE("proxy auto_detect false");
      ////
      ////         //   string strUrl = Context.os().connection_settings_get_auto_config_url();
      ////
      ////         //   if(strUrl.has_char())
      ////         //   {
      ////
      ////         //      TRACE("get_auto_config_url : %s",strUrl);
      ////
      ////         //      if(try_pac_script(strUrl,pszUrl,pproxy))
      ////         //         return;
      ////
      ////         //   }
      ////
      ////         //   if(try_pac_script("http://wpad/wpad.dat",pszUrl,pproxy))
      ////         //      return;
      ////
      ////         //}
      ////
      ////
      ////         pproxy->m_bDirect = true;
      ////
      ////      }

   }


   //void context::on_auth(property_set & set, ::apex::application *      papp, string & strUrl, string & strSessId, __pointer(::account::user) & puser)
   //{

   //   if (::is_null(papp))
   //   {

   //      return;

   //   }

   //   if (set.is_true("raw_http"))
   //   {

   //      return;

   //   }

   //   if (!Sess(papp).account()->url_requires_auth(strUrl))
   //   {

   //      return;

   //   }

   //   string strWorkUrl;

   //   bool bInteractive = set.is_set_false("noninteractive");

   //   puser = App(papp).get_user(strUrl, true, bInteractive);

   //   if (puser.is_null())
   //   {

   //      return;

   //   }

   //   strSessId = puser->m_strSessId;

   //   if (strSessId.is_empty())
   //   {

   //      System.url().string_set(strUrl, "authnone", 1);

   //      return;

   //   }

   //   //System.url().string_set(strUrl, "sessid", strSessId);

   //}


   bool context::open(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession, const char * pszHost, const char * pszProtocol, property_set & set, const char * pszVersion)
   {

      auto tickTimeProfile1 = ::millis::now();

      UNREFERENCED_PARAMETER(pszVersion);

      string strServer = pszHost;

      string strProtocol = pszProtocol;

      __pointer(::apex::application) papp = set["app"].cast < ::apex::application >();

      i32 iPort;

      if (strProtocol == "https")
      {

         iPort = 443;

      }
      else
      {

         iPort = 80;

      }

      if (pszVersion == nullptr || pszVersion[0] == '\0')
      {

         pszVersion = "HTTP/1.1";

      }

      string strUrl(strProtocol + "://" + strServer);

      // Format of script name example "context://server.com/the rain.mp3" => "context://server.com/the%20rain.mp3"
      {

         string strScript = System.url().url_encode(System.url().url_decode(System.url().get_script(strUrl)));

         strScript.replace("+", "%20");

         strScript.replace("%2F", "/");

         strUrl = System.url().set_script(strUrl, strScript);

      }

      property_set setQuery;

      setQuery.parse_url_query(System.url().get_query(strUrl));

      string strIp;

      string strSessId;

      psession = __new(::sockets::http_session(handler, strProtocol, pszHost));

      /*__pointer(::account::user) puser;

      on_auth(set, papp, strUrl, strSessId, puser);*/

      if (strProtocol == "https")
      {

         psession->EnableSSL();

      }

      auto tick1 = ::millis::now();

      bool bConfigProxy = set.is_set_false("no_proxy_config");

      if (strIp.has_char())
      {

         psession->m_strConnectHost = strIp;

      }

      TRACE("just before open open http_session ::http::context::open " __prtick, __pr(tick1.elapsed()));

      if (!psession->open(bConfigProxy))
      {

         TRACE("Not Opened/Connected Result Total time ::http::context::get(\"%s\") " __prtick, strUrl.Left(min(255, strUrl.get_length())).c_str(), __pr(tick1.elapsed()));

         return false;

      }

      TRACE("context::get open time " __prtick, __pr(tick1.elapsed()));

      return true;

   }


   bool context::request(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession, const char * pszRequest, property_set & set)
   {

      TRACE("http context request : %s", pszRequest);

      millis tick1;

      millis tick2;

      bool bSeemsOk;

      i32 iTry = 0;

      i32 iTryCount;

      if (set.has_property("try"))
      {

         iTryCount = set["try"];

         if (iTryCount > 5)
         {

            iTryCount = 5;

         }

      }
      else
      {

         iTryCount = 2;

      }

   retry:

      iTry++;

      bSeemsOk = true;

      try
      {

         if (psession == nullptr)
         {

            bSeemsOk = false;

         }
         else if (!psession->is_valid())
         {

            //handler.remove(psession);

            psession->SetCloseAndDelete();

            bSeemsOk = false;

         }

      }
      catch (...)
      {

         bSeemsOk = false;

      }

      if (!bSeemsOk)
      {

         try
         {

            auto tickBeg = ::millis::now();

            if (!open(handler, psession, System.url().get_server(pszRequest), System.url().get_protocol(pszRequest), set, set["http_protocol_version"]))
            {

               return false;

            }

            TRACE("opening context::request time(%d) = " __prtick, __pr(tickBeg.elapsed()));

         }
         catch (...)
         {

            return false;

         }

      }

      auto tickBegA = ::millis::now();

      try
      {

         auto tickTimeProfile1 = ::millis::now();

         ::apex::application * papp = handler.get_context_application();

         string strRequest = System.url().get_object(pszRequest);

         string strServer = System.url().get_server(pszRequest);

         string strUrl = psession->m_strProtocol + "://" + strServer + strRequest;

         // Format of script name example "context://server.com/the rain.mp3" => "context://server.com/the%20rain.mp3"
         {

            string strScript = System.url().url_encode(System.url().url_decode(System.url().get_script(strUrl)));

            strScript.replace("+", "%20");

            strScript.replace("%2F", "/");

            strUrl = System.url().set_script(strUrl, strScript);

         }

         property_set setQuery;

         setQuery.parse_url_query(System.url().get_query(strUrl));

         string strSessId;

         //__pointer(::account::user) puser;

         //on_auth(set, papp, strUrl, strSessId, puser);

         strRequest = System.url().get_object(strUrl);

         psession->inheaders().clear();
         psession->outheaders().clear();
         psession->inattrs().clear();
         psession->outattrs().clear();
         psession->m_memoryfile.set_size(0);

         psession->inheaders() = set["headers"].propset();

         if (set.has_property("minimal_headers") && (bool)set["minimal_headers"])
         {

            psession->m_request.attrs()["minimal_headers"] = true;

         }

         if (set.has_property("file"))
         {

            psession->m_pfile = set["file"].cast < ::file::file >();

         }

         if (set.has_property("int_scalar_source_listener"))
         {

            psession->::int_scalar_source::m_plistener = set["int_scalar_source_listener"].cast < int_scalar_source::listener >();

         }
         else
         {

            psession->::int_scalar_source::m_plistener = nullptr;

         }

         if (set["cookies"].cast < ::http::cookies >() != nullptr && set["cookies"].cast < ::http::cookies >()->get_size() > 0)
         {

            psession->request().header(__id(cookie)) = set["cookies"].cast < ::http::cookies >()->get_cookie_header();

         }

         //if (set["user"].cast < ::account::user >() != nullptr && set["user"].cast < ::account::user >()->m_phttpcookies != nullptr && !(bool)set["disable_ca2_user_cookies"])
         //{

         //   psession->request().header(__id(cookie)) = set["user"].cast < ::account::user >()->m_phttpcookies->get_cookie_header();

         //}

         if (set.has_property(__id(cookie)) && set[__id(cookie)].get_string().has_char())
         {

            psession->request().header(__id(cookie)) = set[__id(cookie)];

         }

         psession->m_host = System.url().get_server(pszRequest);

         psession->m_strHost = System.url().get_server(pszRequest);

         psession->m_request.m_propertysetHeader[__id(host)] = psession->m_host;

         set["http_body_size_downloaded"] = &psession->m_body_size_downloaded;

         psession->m_scalarsourceDownloadedRate.m_plistener = set["http_downloaded_rate_listener"].cast < ::double_scalar_source::listener >();

         psession->m_scalarsourceDownloadedRate.m_id = set["http_downloaded_rate_id"].get_id();

         psession->m_scalarsourceDownloaded.m_plistener = set["http_downloaded_listener"].cast < ::int_scalar_source::listener >();

         psession->m_scalarsourceDownloaded.m_id = set["http_downloaded_id"].get_id();

         bool bPost;

         bool bPut;

         if (set["put"].cast < ::file::file >() || set(__id(http_method)) == "PUT")
         {

            bPost = false;

            bPut = true;

            psession.cast < ::sockets::http_put_socket>()->m_file = set["put"].cast < ::file::file >();

            psession->request("PUT", strRequest);

         }
         else if (set["post"].propset().has_element() || set(__id(http_method)) == "POST")
         {

            bPost = true;

            bPut = false;

            psession.cast < ::sockets::http_post_socket>()->m_fields = set["post"].propset();

            if (set.has_property("multipart"))
            {

               psession.cast < ::sockets::http_post_socket>()->m_pmultipart = set["multipart"].cast < ::sockets::multipart >();

            }

            psession->request("POST", strRequest);

         }
         else
         {

            bPost = false;

            bPut = false;

            psession->request("GET", strRequest);

         }

         handler.add(psession);

         i32 iIteration = 0;

         //::apex::live_signal keeplive;

         //if (papp != nullptr)
         //{

         //   keeplive.keep(papp);

         //   keeplive.keep(&Sess(papp));

         //   keeplive.keep(&Sys(papp));

         //}

         TRACE("opening preparation context::request time(%d) = " __prtick, __pr(tickBegA.elapsed()));

         tick1 = value("dw").millis();

         tick2.Now();

         TRACE("Higher Level Diagnosis : iNTERTIMe context::request time(%d) = " __prtick __prtick __prtick, iIteration, __pr(tick1), __pr(tick2), __pr(tick2 - tick1));

         while ((handler.get_count() > 0 && !psession->m_bRequestComplete) && (::get_task() == nullptr || ::thread_get_run()))
            //while(psession->get_count() > 0 && !psession->m_bRequestComplete) // should only exit in case of process exit signal
         {

            tick1 = ::millis::now();

            handler.select(240, 0);

//            keeplive.keep_alive();

            set["http_content_length"] = psession->m_content_length;

            if (set.has_property("cancel"))
            {

               if (set["cancel"].get_bool())
               {

                  break;

               }

            }

            double dRateDownloaded = 0.0;

            i64 iContentLength = set["http_content_length"].i64();

            i64 iBodySizeDownloaded = set["http_body_size_downloaded"].i64();

            if (iContentLength > 0)
            {

               if (iBodySizeDownloaded > 0.0)
               {

                  dRateDownloaded = (double)iBodySizeDownloaded / (double)iContentLength;

               }

            }

            set["http_rate_downloaded"] = dRateDownloaded;

            psession->m_scalarsourceDownloadedRate.set_scalar(::scalar_none, dRateDownloaded);

            psession->m_scalarsourceDownloaded.set_scalar(::scalar_none, iBodySizeDownloaded);

            if (psession->m_estatus == error_connection_timed_out
               || psession->m_estatus == error_on_connection_timeout)
            {

               break;

            }

            TRACE("context::request " __prtick, __pr(tick1.elapsed()));

            iIteration++;

         }

///         keeplive.keep_alive();

         (*this)["dw"].millis().Now();

         set["get_headers"] = psession->outheaders();

         set["get_attrs"] = psession->outattrs();

         string strCookie = psession->response().cookies().get_cookie_header();

         set[__id(cookie)] = strCookie;

         i32 iStatusCode = psession->outattr("http_status_code");

         if (set.has_property("cancel") && set["cancel"].get_bool())
         {

            psession->m_estatus = error_connection_cancelled;

         }
         else if (iStatusCode == 0)
         {

#if defined(BSD_STYLE_SOCKETS)

            if (psession.is_set()
               && psession->m_psslcontext != nullptr
               && psession->m_psslcontext->m_pclientcontext != nullptr
               && psession->m_psslcontext->m_pclientcontext->m_psslcontext != nullptr
               && psession->m_psslcontext->m_iSslCtxRetry == 1 && iTry < iTryCount)
            {

               goto retry;

            }

#endif

         }
         else if (iStatusCode != 200)
         {

            if (iTry < iTryCount)
            {

               psession = nullptr;

               goto retry;

            }

         }

         ::estatus     estatus;

         if (::failed(psession->m_estatus))
         {

            estatus = psession->m_estatus;

         }
         else if ((iStatusCode >= 200 && iStatusCode <= 299) || (psession != nullptr && psession->outattr("http_status_code").is_empty()))
         {

            estatus = ::success;

         }
         else if (iStatusCode >= 300 && iStatusCode <= 399)
         {
            if (psession != nullptr)
            {

               string strCa2Realm = psession->outheader("ca2realm-x");

               if (::str::begins_ci(strCa2Realm, "n7ot licensed: "))
               {

                  TRACE("Not Licensed Result Total time ::http::context::get(\"%s\") " __prtick, strUrl.Left(min(255, strUrl.get_length())).c_str(), __pr(tick1.elapsed()));

                  string strLocation = psession->outheader("Location");

                  psession.release();

                  __throw(not_licensed(strCa2Realm, strLocation));

                  return false;

               }

            }

         }
         else
         {

            estatus = error_http;

         }

         set["get_status"] = (i64)estatus;

         TRACE("Total time ::http::context::get(\"%s\") " __prtick, strUrl.Left(min(255, strUrl.get_length())).c_str(), __pr(tick1.elapsed()));

      }
      catch (...)
      {

         if (iTry >= iTryCount)
         {

            return false;

         }

         goto retry;

      }

      if (psession != nullptr)
      {

         if (set.has_property("get_response"))
         {

            set["get_response"] = string((const char *)psession->GetDataPtr(), psession->GetContentLength());

         }

         if (set.has_property("get_memory"))
         {

            memory_base * pmemory = set.cast < memory_base >("get_memory");

            if (pmemory != nullptr)
            {

               pmemory->assign(psession->GetDataPtr(), psession->GetContentLength());

            }
            else
            {

               set["get_memory"] = __new(memory(psession->GetDataPtr(), psession->GetContentLength()));

            }

         }

      }

      return true;

   }


   bool context::get(::http::session & session, const char * pszUrl, string & str, property_set & set)
   {

      bool bOk = http_get(session.m_handler, session.m_psocket, pszUrl, set);

      if (bOk)
      {

         const char * pszData = (const char *)session.m_psocket->GetDataPtr();

         strsize iSize = session.m_psocket->GetContentLength();

         str = string(pszData, iSize);

      }

      return bOk;

   }


   string context::get(::http::session & session, const char * pszUrl, property_set & set)
   {

      string str;

      if (!get(session, pszUrl, str, set))
      {

         return "";

      }

      return str;

   }



   bool context::http_get(::sockets::socket_handler & handler, __pointer(::sockets::http_client_socket) & psocket, const char * pszUrl, property_set & set)
   {

      auto ptask = ::get_task();

      __keep(ptask->value("work_url"), pszUrl);

      i64 iHttpGetSerial = ++System.sockets().m_lHttpGetSerial;

      TRACE("");
      TRACE("");
      TRACE("------------------------------------------------------");
      TRACE(__prhttpget "Start: %s", iHttpGetSerial, pszUrl);

      set["http_get_serial"] = iHttpGetSerial;

      auto tickStart = millis::now();

      int iTry = 0;

      int iTryCount;

      if (set.has_property("try"))
      {

         iTryCount = set["try"];

         if (iTryCount > 5)
         {

            iTryCount = 5;

         }

      }
      else
      {

         iTryCount = 2;

      }

//#ifdef BSD_STYLE_SOCKETS
      retry :
//#endif

      iTry++;

      auto tickTimeProfile1 = ::millis::now();

      string strServer = System.url().get_root(pszUrl);

      string strProtocol = System.url().get_protocol(pszUrl);

      string strObject = System.url().get_object(pszUrl);

      __pointer(::apex::application) papp = set["app"].cast < ::apex::application >();

      __pointer(::apex::application) pappAgent = papp;

      i32 iPort;

      if (strProtocol == "https")
      {

         iPort = 443;

      }
      else
      {

         iPort = 80;

      }

      string strVersion = set["http_protocol_version"];
      if (strVersion.is_empty())
      {

         strVersion = "HTTP/1.1";

      }

      string strUrl(pszUrl);

//      bool bSessionAccount = !set.is_true("raw_http") && ::is_set(get_context_session()) && ::is_set(psession->account());

      bool bSessionAccount = !set.is_true("raw_http") && ::is_set(get_context_session()) ;

//      single_lock slFontopus(bSessionAccount ? psession->account()->mutex() : nullptr);

      string strIp;

      string strSessId;

      int iRetrySession = 0;

   //retry_session:

   //   __pointer(::account::user) puser;

      if (bSessionAccount)
      {

//         on_auth(set, papp, strUrl, strSessId, puser);

         if (strSessId.has_char())
         {

            set[__id(cookie)] = ::str::has_char(set[__id(cookie)], "", "; ") + "sessid=" + strSessId;

         }

         // Format of script name example "context://server.com/the rain.mp3" => "context://server.com/the%20rain.mp3"
         {

            string strScript = System.url().url_encode(System.url().url_decode(System.url().get_script(strUrl)));

            strScript.replace("+", "%20");

            strScript.replace("%2F", "/");

            strUrl = System.url().set_script(strUrl, strScript);

         }

      }

      bool bPost;

      bool bPut;

      if (set["put"].cast < ::file::file >() || set(__id(http_method)) == "PUT")
      {

         bPost = false;

         bPut = true;

         psocket = __new(::sockets::http_put_socket(handler, strUrl));

         dynamic_cast <::sockets::http_put_socket *> (psocket.m_p)->m_file = set["put"].cast < ::file::file >();

         psocket->m_emethod = ::sockets::http_method_put;

      }
      else if (set["post"].propset().has_element() || set(__id(http_method)) == "POST")
      {

         bPost = true;

         bPut = false;

         psocket = __new(::sockets::http_post_socket(handler, strUrl));

         dynamic_cast <::sockets::http_post_socket *> (psocket.m_p)->m_fields = set["post"].propset();

         if (set.has_property("multipart"))
         {

            psocket.cast < ::sockets::http_post_socket>()->m_pmultipart = set["multipart"].cast < ::sockets::multipart >();

         }

         psocket->m_emethod = ::sockets::http_method_post;

      }
      else
      {

         bPost = false;

         bPut = false;

         psocket = __new(::http::get_socket(handler, strUrl));

         psocket->m_emethod = ::sockets::string_http_method(set(__id(http_method), "GET"));

      }

      if (pappAgent.is_set())
      {

         psocket->set_context_object(pappAgent);

      }

      psocket->format_topic_text(__prhttpget, iHttpGetSerial);

      psocket->m_bEnablePool = handler.PoolEnabled();

      if ((bool)set["disable_common_name_cert_check"])
      {

         psocket->enable_cert_common_name_check(false);

      }

      if (strProtocol == "https")
      {

         psocket->m_strTlsHostName = System.url().get_server(strUrl);

      }

      if (set["http_listener"].cast < ::http::listener >() != nullptr)
      {

         psocket->::sockets::http_socket::m_plistener = set["http_listener"].cast < ::http::listener >();

      }

      psocket->inheaders().add(set["headers"].propset());

      if (set.has_property("progress_listener"))
      {

         psocket->m_progress.m_plistener = set["progress_listener"].cast < progress_listener >();

      }

      if (set.has_property("int_scalar_source_listener"))
      {

         psocket->::int_scalar_source::m_plistener = set["int_scalar_source_listener"].cast < int_scalar_source::listener >();

      }

      if (set.has_property("minimal_headers") && (bool)set["minimal_headers"])
      {

         psocket->m_request.attrs()["minimal_headers"] = true;

      }

      if (set.has_property("only_headers") && (bool)set["only_headers"])
      {

         psocket->m_bOnlyHeaders = true;

      }

      if (set.has_property("noclose") && !(bool)set["noclose"])
      {

         psocket->m_bNoClose = false;

      }

      if (set.has_property("file"))
      {

         psocket->m_pfile = set["file"].cast < ::file::file >();

      }

      if (set["cookies"].cast < ::http::cookies >() != nullptr && set["cookies"].cast < ::http::cookies >()->get_size() > 0)
      {

         if (set["cookies"].cast < ::http::cookies >()->find_cookie("sessid") >= 0)
         {

            set["cookies"].cast < ::http::cookies >()->set_cookie("sessid", strSessId);

         }

         psocket->request().header(__id(cookie)) = set["cookies"].cast < ::http::cookies >()->get_cookie_header();

      }

      //if (set["user"].cast < ::account::user >() != nullptr && set["user"].cast < ::account::user >()->m_phttpcookies != nullptr && !(bool)set["disable_ca2_user_cookies"])
      //{

      //   if (set["user"].cast < ::account::user >()->m_phttpcookies->find_cookie("sessid") >= 0)
      //   {

      //      set["user"].cast < ::account::user >()->m_phttpcookies->set_cookie("sessid", strSessId);

      //   }

      //   psocket->request().header(__id(cookie)) = set["user"].cast < ::account::user >()->m_phttpcookies->get_cookie_header();

      //}

      if (set.has_property(__id(cookie)) && set[__id(cookie)].get_string().has_char())
      {

         psocket->request().header(__id(cookie)) = set[__id(cookie)];

      }

      if (!psocket->m_bNoClose)
      {

         psocket->SetCloseOnComplete();

      }

      if (strProtocol == "https")
      {

         psocket->EnableSSL();

      }

      auto tick1 = ::millis::now();

      bool bConfigProxy = !set.has_property("no_proxy_config") || !(bool)set["no_proxy_config"];

      millis tickTotalTimeout = set["timeout"].i64();

      set["http_body_size_downloaded"] = &psocket->m_body_size_downloaded;

      psocket->m_scalarsourceDownloadedRate.m_plistener = set["http_downloaded_rate_listener"].cast < ::double_scalar_source::listener >();

      psocket->m_scalarsourceDownloadedRate.m_id = set["http_downloaded_rate_id"].get_id();

      psocket->m_scalarsourceDownloaded.m_plistener = set["http_downloaded_listener"].cast < ::int_scalar_source::listener >();

      psocket->m_scalarsourceDownloaded.m_id = set["http_downloaded_id"].get_id();

      if (tickTotalTimeout <= 0)
      {

         tickTotalTimeout = 30_s;

      }

      if (strIp.has_char())
      {

         psocket->m_strConnectHost = strIp;

      }

      string_array straProxy;

      if (set.has_property("proxy"))
      {

         straProxy.explode(":", set["proxy"].get_string());

         if (straProxy.get_count() != 2 || !psocket->proxy_open(straProxy[0], atoi(straProxy[1])))
         {

            set["get_status"] = (i64)error_http;

            auto tick2 = ::millis::now();

            TRACE(__prhttpget "Not Opened/Connected Result Total time ::http::context::get(\"%s\") " __prtick, iHttpGetSerial, strUrl.Left(min(255, strUrl.get_length())).c_str(), __pr(tick1.elapsed()));

            return false;

         }

      }
      else if (!psocket->open(bConfigProxy))
      {

         set["get_status"] = (i64)error_http;

         TRACE(__prhttpget "Not Opened/Connected Result Total time ::http::context::get(\"%s\") " __prtick, iHttpGetSerial, strUrl.Left(min(255, strUrl.get_length())).c_str(), __pr(tick1.elapsed()));

         return false;

      }

      handler.add(psocket);

      i32 iIteration = 1;

      //::apex::live_signal keeplive;

      if ((bool)set["noloop"])
      {

         return true;

      }

      if (set.has_property("connection_retry"))
      {

         psocket->SetConnectionRetry(set["connection_retry"].i32());

      }
      //else
      //{

      //   psocket->SetConnectionRetry(3);

      //}

      //if (papp != nullptr)
      //{

      //   keeplive.keep(papp);
      //   keeplive.keep(&Sess(papp));
      //   keeplive.keep(&Sys(papp));

      //}

      psocket->m_bEnablePool = handler.PoolEnabled();

      if (handler.PoolEnabled())
      {

         psocket->SetRetain();

      }

      i64 iContentLength = -1;

      i64 iBodySizeDownloaded = -1;

      int iEnteredLoop = 0;

      tick1 = ::millis::now();

      while (handler.get_count() > 0 && (::get_task() == nullptr || ::thread_get_run()))
      {

         if (tickStart.elapsed() > tickTotalTimeout)
         {

            TRACE(__prhttpget "FAILING BY Timeout after %d steps " __prtick, iHttpGetSerial, iIteration, __pr(tick1.elapsed()));

            break;

         }

         iEnteredLoop = 1;

         auto iSelectTimeoutMillis = min(tickTotalTimeout, (tickTotalTimeout - tickStart.elapsed()));

         auto iSelectTimeoutSeconds = iSelectTimeoutMillis.seconds();

         iSelectTimeoutSeconds = max(1, iSelectTimeoutSeconds);

         iContentLength = psocket->m_content_length;

         handler.select((i32)iSelectTimeoutSeconds, 0);

         set["http_content_length"] = iContentLength;

         double dRateDownloaded = 0.0;

         i64 iBodySizeDownloadedNow = set["http_body_size_downloaded"].i64();

         if (iBodySizeDownloadedNow > iBodySizeDownloaded)
         {

            iBodySizeDownloaded = iBodySizeDownloadedNow;

            if (iBodySizeDownloaded > 0)
            {

               tickStart = millis::now();

            }

         }

         if (set.has_property("cancel") && set["cancel"].get_bool())
         {

            TRACE(__prhttpget "FAILING BY Cancellation at step %d " __prtick, iHttpGetSerial, iIteration, __pr(tick1.elapsed()));

            break;

         }

         if (iContentLength > 0)
         {

            if (iBodySizeDownloaded > 0.0)
            {

               dRateDownloaded = (double)iBodySizeDownloaded / (double)iContentLength;

            }

         }

         set["http_rate_downloaded"] = dRateDownloaded;

         psocket->m_scalarsourceDownloadedRate.set_scalar(::scalar_none, dRateDownloaded);

         psocket->m_scalarsourceDownloaded.set_scalar(::scalar_none, iBodySizeDownloaded);

//         keeplive.keep_alive();

         if (psocket->m_estatus == error_connection_timed_out
            || psocket->m_estatus == error_on_connection_timeout)
         {

            TRACE(__prhttpget "FAILING BY Connection Timeout after %d steps " __prtick, iHttpGetSerial, iIteration, __pr(tick1.elapsed()));

            break;

         }

         if (psocket->m_b_complete)
         {

            TRACE(__prhttpget "Complete! in %d steps " __prtick, iHttpGetSerial, iIteration, __pr(tick1.elapsed()));

            break;

         }

         if (iContentLength >= 0)
         {

            TRACE(__prhttpget "%d. step " __prtick " Content-Length:%" PRIi64, iHttpGetSerial, iIteration, __pr(tick1.elapsed()), iContentLength);

         }
         else
         {

            TRACE(__prhttpget "%d. step " __prtick, iHttpGetSerial, iIteration, __pr(tick1.elapsed()));

         }


         if (HTTP_DEBUG_LEVEL >= DEBUG_LEVEL_SICK)
         {

            TRACE(__prhttpget "iSelectTimeoutSeconds=%d\n", iHttpGetSerial, iSelectTimeoutSeconds);

         }

         iIteration++;

      }

//      keeplive.keep_alive();

      set["get_headers"] = psocket->outheaders();

      set["get_attrs"] = psocket->outattrs();

      string strCookie = psocket->response().cookies().get_cookie_header();

      set[__id(cookie)] = strCookie;

      ::estatus     estatus = error_failed;

      i32 iStatusCode = psocket->outattr("http_status_code");

      set["http_status_code"] = iStatusCode;

      string strStatus = psocket->outattr("http_status");

      set["http_status"] = strStatus;

      iContentLength = set["http_content_length"].i64();

      iBodySizeDownloaded = set["http_body_size_downloaded"].i64();

      INFO(__prhttpget "%s Status: %d - %s, Content Length: %" PRId64 ", Body Download: %" PRId64 ", Loop: %d, %s",
         iHttpGetSerial,
         strUrl.c_str(),
         iStatusCode,
         strStatus.c_str(),
         iContentLength,
         iBodySizeDownloaded,
         iEnteredLoop,
         psocket->m_b_complete ? "Finished!" : "Incomplete!"
      );

      if (set.has_property("cancel") && set["cancel"].get_bool())
      {

         psocket->m_estatus = error_connection_cancelled;

      }
      else if (iStatusCode == 0)
      {

         millis tickElapse = tickStart.elapsed();

         if (iTry < iTryCount && tickElapse < tickTotalTimeout)
         {

            task_sleep(300);

            if (::thread_get_run())
            {

               goto retry;

            }

         }

         TRACE(__prhttpget "URL: %s Too much tries (%d)", iHttpGetSerial, strUrl.c_str(), iTry);

         estatus = error_http;

      }
      else if (::failed(psocket->m_estatus))
      {

         estatus = psocket->m_estatus;

      }
      else if ((iStatusCode >= 200 && iStatusCode <= 299) || psocket->outattr("http_status_code").is_empty())
      {

         estatus = ::success;

      }
      else if (iStatusCode >= 300 && iStatusCode <= 399)
      {

         string strCa2Realm = psocket->outheader("ca2realm-x");

         if (::str::begins_ci(strCa2Realm, "not licensed: "))
         {

            auto tick2 = ::millis::now();

            TRACE(__prhttpget "Not Licensed Result Total time ::http::context::get(\"%s\") " __prtick, iHttpGetSerial, strUrl.Left(min(255, strUrl.get_length())).c_str(), __pr(tick1.elapsed()));

            string strLocation = psocket->outheader("Location");

            __throw(not_licensed(strCa2Realm, strLocation));

            return false;

         }

         string strLocation = psocket->outheader("locationd");

         if (set.has_property("redirect_location"))
         {

            set["redirect_location"] = strLocation;

            estatus = ::success_http_redirection;

         }
         else if (strLocation.has_char())
         {

            if (strLocation.find_ci("http://") == 0 || strLocation.find_ci("https://") == 0)
            {

               return http_get(handler, psocket, strLocation, set);

            }
            else
            {

               strLocation = System.url().get_protocol(pszUrl) + System.url().get_server(pszUrl) + System.url().get_object(strLocation);

               return http_get(handler, psocket, strLocation, set);

            }

         }

      }
      else if (iStatusCode == 401)
      {

         //if (strSessId.has_char() && puser.is_set() && iRetrySession < 3)
         //{

         //   psession->account()->not_auth(pszUrl);

         //   iRetrySession++;

         //   goto retry_session;

         //}

         estatus = error_http;

      }
      else
      {

         estatus = error_http;

      }

      set["get_status"] = estatus;

      if (set["http_listener"].cast < ::http::listener >() != nullptr)
      {

         set["http_listener"].cast < ::http::listener >()->on_http_complete(psocket, estatus);

      }

      if (set.has_property("get_response"))
      {

         const char * pszData = (const char *)psocket->GetDataPtr();

         strsize iSize = psocket->GetContentLength();

         string strResponse(pszData, iSize);

         set["get_response"] = strResponse;

      }

      if (set.has_property("get_memory"))
      {

         memory_base * pmemory = set.cast < memory_base >("get_memory");

         if (pmemory != nullptr)
         {

            pmemory->assign(psocket->GetDataPtr(), psocket->GetContentLength());

         }
         else
         {

            set["get_memory"] = __new(memory(psocket->GetDataPtr(), psocket->GetContentLength()));

         }

      }

      TRACE(__prhttpget "Total time " __prtick, iHttpGetSerial, __pr(tick1.elapsed()));

      return true;

   }


   void context::get(::message::message * pmessage)
   {

      SCAST_PTR(message, pmessageMessage, pmessage);

      if (pmessageMessage == nullptr)
      {

         return;

      }

      //SCAST_PTR(message, pmessage, pmessage);

      ::url_domain domain;

      domain.create(System.url().get_server(pmessageMessage->m_strUrl));

      if (domain.m_strRadix == "ca2" && ::str::begins(System.url().get_object(pmessageMessage->m_strUrl), astr.MatterUri))
      {

         string strUrl(pmessageMessage->m_strUrl);

         property_set& set = pmessage->get_property_set();

         single_lock sl(m_pmutexDownload, true);

         if (!(m_straDownloading.contains(strUrl)) && !exists(pmessageMessage->m_strUrl, set))
         {

            sl.unlock();

            pmessageMessage->m_estatusRet = error_http;

            pmessage->m_bRet = false;

            return;

         }

      }

      pmessage->get_property_set() = process_set(*pmessage->m_pset, pmessageMessage->m_strUrl);

      ::sockets::socket_handler handler(get_context_object());

      property_set & set = pmessage->get_property_set();

      if (pmessageMessage->m_setPost.get_count() > 0)
      {

         set["post"] = pmessageMessage->m_setPost;

      }

      if (pmessageMessage->m_setHeaders.get_count() > 0)
      {

         set["headers"] = pmessageMessage->m_setHeaders;

      }

      if (pmessageMessage->m_pcookies != nullptr && pmessageMessage->m_pcookies->get_count() > 0)
      {

         set["cookies"] = pmessageMessage->m_pcookies;

      }

      if (pmessageMessage->m_strVersion.has_char())
      {

         set["http_protocol_version"] = pmessageMessage->m_strVersion;

      }

      __pointer(::sockets::http_client_socket) psocket;

      if (!http_get(handler, psocket, pmessageMessage->m_strUrl, set))
      {

         pmessageMessage->m_estatusRet = (::estatus) set["get_status"].i64();

         pmessageMessage->m_bRet = false;

         return;

      }

      pmessageMessage->m_estatusRet = (::estatus) set["get_status"].i64();

      pmessageMessage->m_setHeaders = psocket->outheaders();

      i32 iStatusCode = psocket->outattr("http_status_code");

      pmessage->m_bRet = iStatusCode == 200;

      return;

   }


   bool context::download(sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession, const char * pszRequest, payload varFile, property_set & set)
   {

      file_pointer spfile = Context.file().get_file(varFile,
         ::file::type_binary | ::file::mode_create | ::file::mode_read_write | ::file::defer_create_directory);

      set["file"] = spfile;

      bool bOk = request(handler, psession, pszRequest, set);

      set["file"].null();

      return bOk;

   }


   bool context::download(const char * pszUrl, payload varFile, property_set & set)
   {

      ::sockets::socket_handler handler(get_context_object());

      __pointer(::sockets::http_client_socket) psocket;

      bool bOk = false;

      {

         auto rfile = Context.file().get_file(varFile,
            ::file::type_binary | ::file::mode_create | ::file::mode_read_write | ::file::defer_create_directory);

         if (!rfile)
         {

            return false;

         }

         set["file"] = (::file_pointer) rfile;

         bOk = http_get(handler, psocket, pszUrl, set);

         set["file"].null();

      }

      if (!bOk)
      {

         return false;

      }

      return true;

   }


   bool context::exists(const char * pszUrl, ::property_set & set)
   {

      ::file::enum_type etype = ::file::type_none;

      bool bExists = is_file_or_dir(pszUrl, set, &etype);

      return bExists && etype != ::file::type_none;

   }


   bool context::is_file_or_dir(const char * pszUrl, ::property_set & set, ::file::enum_type * petype)
   {

      single_lock sl(m_pmutexDownload, true);

      i32 iStatusCode = 0;

      try
      {

         while (m_straExists.contains(pszUrl))
         {

            sl.unlock();

            millis_sleep(100);

            sl.lock();

         }

         m_straExists.add(pszUrl);

         sl.unlock();

         ::sockets::socket_handler handler(get_context_object());

         set["only_headers"] = true;

         ::url_domain domain;

         domain.create(System.url().get_server(pszUrl));

         if (::str::begins(System.url().get_object(pszUrl), astr.MatterUri))
         {

            set["raw_http"] = true;

         }

         __pointer(::sockets::http_client_socket) psocket;

         if (!http_get(handler, psocket, pszUrl, set))
         {

            sl.lock();

            m_straExists.remove(pszUrl);

            if (::is_set(petype))
            {

               *petype = ::file::type_none;

            }

            return false;

         }

         iStatusCode = psocket->outattr("http_status_code");

         sl.lock();

      }
      catch (...)
      {

      }

      m_straExists.remove(pszUrl);

      bool bExists = iStatusCode == 200;

      if (::is_set(petype))
      {

         if (bExists)
         {

            *petype = ::file::type_element;

         }
         else
         {

            *petype = ::file::type_none;

         }

      }

      return bExists;

   }


   payload context::length(const char * pszUrl, ::property_set & set)
   {

      ::sockets::socket_handler handler(get_context_object());

      set["only_headers"] = true;

      set["minimal_headers"] = true;

      ::url_domain domain;

      domain.create(System.url().get_server(pszUrl));

      if (::str::begins(System.url().get_object(pszUrl), astr.MatterUri))
      {

         set["disable_ca2_sessid"] = true;

      }

      __pointer(::sockets::http_client_socket) psocket;

      if (http_get(handler, psocket, pszUrl, set))
      {

         return false;

      }

      i32 iStatusCode = psocket->outattr("http_status_code");

      if (iStatusCode == 200)
      {

         return psocket->outheader(__id(content_length));

      }
      else
      {

         return payload(::e_type_null);

      }

   }


   string context::gmdate(time_t t)
   {

      if (t == 0)
      {

         t = ::time(nullptr);

      }

      struct tm tp;

#ifdef _WIN32

      ::memcpy_dup(&tp, gmtime(&t), sizeof(tp));

#else

      gmtime_r(&t, &tp);

#endif

      const char * days[7] = { "Sunday", "Monday",
                             "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
      };

      const char * months[12] = { "Jan", "Feb", "Mar", "Apr", "May",
                                "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
      };

      char strDateTime[1024];

      sprintf(strDateTime, "%s, %02d-%s-%04d %02d:%02d:%02d GMT",
         days[tp.tm_wday],
         tp.tm_mday,
         months[tp.tm_mon],
         tp.tm_year + 1900,
         tp.tm_hour,
         tp.tm_min,
         tp.tm_sec);

      return strDateTime;

   }


   //void context::set_proxy_auth(::account::user * puser, ::sockets::http_client_socket * psocket)
   //{

   //   string strUserName;
   //   string strPassword;
   //   string strUserNameFile;
   //   string strPasswordFile;
   //   string strSection;

   //   strSection.Format("proxy_auth\\%s.%s", puser->m_strLogin.c_str(), "proxy_auth");

   //   strUserNameFile = Context.dir().appdata() / strSection + "_1";

   //   strPasswordFile = Context.dir().appdata() / strSection + "_2";

   //   bool bOk = true;

   //   if (!System.crypto().file_get(strUserNameFile, strUserName, nullptr, get_context_application()) || strUserName.is_empty())
   //   {

   //      bOk = false;

   //   }

   //   if (!System.crypto().file_get(strPasswordFile, strPassword, nullptr, get_context_application()) || strPassword.is_empty())
   //   {

   //      bOk = false;

   //   }

   //   if (bOk)
   //   {

   //      psocket->m_strUserNameFile = strUserNameFile;

   //      psocket->m_strPasswordFile = strPasswordFile;

   //   }
   //   else
   //   {

   //      if (psession->get_auth("context/account/proxy_authenticate.xhtml", strUserName, strPassword))
   //      {

   //         System.crypto().file_set(strUserNameFile, strUserName, nullptr, get_context_application());

   //         System.crypto().file_set(strPasswordFile, strPassword, nullptr, get_context_application());

   //         psocket->m_strUserNameFile = strUserNameFile;

   //         psocket->m_strPasswordFile = strPasswordFile;

   //      }

   //   }

   //}


   //void context::clean_proxy_auth(::account::user * puser)
   //{

   //   string strSection;

   //   strSection.Format("proxy_auth\\%s.%s", puser->m_strLogin.c_str(), "proxy_auth");

   //   Context.file().del(Context.dir().appdata() / strSection + "_1");

   //   Context.file().del(Context.dir().appdata() / strSection + "_2");

   //}


   bool context::put(const char * pszUrl, memory_base & memory, property_set & set)
   {

      ::memory_file file(memory);

      return put(pszUrl, &file, set);

   }


   bool context::put(const char * pszUrl, file_pointer  pfile, property_set & set)
   {

      set["put"] = pfile;

      set["noclose"] = false;

      return get(pszUrl, set);

   }


   bool context::request(const char * pszMethod, const char * pszUrl, property_set & set)
   {

      set[__id(http_method)] = pszMethod;

      return get(pszUrl, set);

   }


} // namespace http



