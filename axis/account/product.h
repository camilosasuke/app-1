//
//  account_license.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 11/12/18.
//


namespace account
{


   class CLASS_DECL_AXIS product :
      virtual public object
   {
   public:
      
      
      ::datetime::time     m_timeRequest;
      string               m_strAppId;
      ::estatus                 m_estatus;
      ::estatus                 m_estatusLicensing;
      ::datetime::time     m_timeValid;
      //bool                 m_bInteractive;
      string               m_strGateway;
      
      
      product(::layered * pobjectContext);
      virtual ~product();
      
      
      virtual void license(string strAppId, bool bInteractive);
      
      virtual bool do_license(string strAppId, bool bInteractive);
      
      virtual void _do_license(string strAppId, bool bInteractive);
      
      virtual bool is_ok();
      
      virtual bool is_licensed();
      
      
   };


} // namespace account



