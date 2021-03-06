#pragma once


class CLASS_DECL_APEX apex_main_data :
   public apex_main_struct,
   virtual public ::object
{
public:


   int                              m_iPathInstallFolderExeArg;
   bool                             m_bFork;
   int                              m_argc;
   char **                          m_argv;
   wchar_t **                       m_wargv;
   int                              m_iExitCode;
   string                           m_strCommandLine;
   string                           m_strStandalone;
   LPFN_MAIN_RUNNER                 m_mainrunnera[64];
   ::edisplay                       m_edisplay;
   ::eactivation                    m_eactivation;
   string                           m_strAppId;
   ::file::path                     m_pathCacheDir;

#ifdef WINDOWS

   HINSTANCE                        m_hinstance;
   HINSTANCE                        m_hPrevInstance;

#endif


   apex_main_data();
   virtual ~apex_main_data();


   void set_main_struct(const apex_main_struct  & mainstruct);


   void system_construct(int argc, char** argv);
   void system_construct(int argc, wchar_t** argv);

   void system_construct(const char* pszCommandLine, const ::edisplay& edisplay = ::e_display_none);
   void system_construct(os_local* poslocal, const ::edisplay& edisplay = ::e_display_none);

#ifdef WINDOWS_DESKTOP

   void system_construct(HINSTANCE hinstance, HINSTANCE hPrevInstance, char * pCmdLine, i32 nCmdShow);

#elif defined(_UWP)

   void system_construct(Array < String^ >^ refstra);

#endif

   string get_arg(int i);

   bool is_console_app() const;


};
