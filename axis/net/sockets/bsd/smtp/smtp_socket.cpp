#include "framework.h"
#include "axis/net/_net.h"


namespace sockets
{


   smtp_socket::smtp_socket(base_socket_handler& h) :
      ::object(&h),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h)
   {

      SetLineProtocol();

   }


   void smtp_socket::OnLine(const string & line)
   {

      SetNonblocking(false);
      ::str::parse pa(line);
      string code = pa.getword();

      code.make_upper();
      if(m_estate == state_initial)
      {
         if(code == "220")
         {
            m_estate = state_hello;
            //print("HELO localhost\r\n");
            print("EHLO account.ca2.cc\r\n");
         }
      }
      else if(m_estate == state_hello)
      {
         if(code == "250" || code.compare_ci("250-Auth") == 0)
         {
            if(code.compare_ci("250-Auth") == 0 || pa.getword().compare_ci("auth") == 0)
            {
               string_array stra;
               stra.explode(" ", pa.getrest());
               stra.trim();
               if(stra.contains_ci("login"))
               {
                  m_estate = state_auth_login;
                  print("AUTH LOGIN\r\n");
               }
            }
            else
            {
               m_estate = state_sender;
               print("MAIL FROM: " + m_pemail->m_addressSender.to_string() + "\r\n");
            }
         }
      }
      else if(m_estate == state_auth_login)
      {
         if(code == "334")
         {
            string strWord = pa.getword();
            string strRequest = System.base64().decode(strWord);
            string strResponse;
            if(::str::find_ci("username", strRequest) >= 0)
            {
               strResponse = System.base64().encode(Context.file().as_string("C:\\sensitive\\sensitive\\seed\\default_sendmail_user.txt"));
               print(strResponse + "\r\n");
            }
            else if(::str::find_ci("password", strRequest) >= 0)
            {
               strResponse = System.base64().encode(Context.file().as_string("C:\\sensitive\\sensitive\\seed\\default_sendmail_pass.txt"));
               print(strResponse + "\r\n");
            }
         }
         else if(code == "235")
         {
            m_estate = state_sender;
            print("MAIL FROM: " + m_pemail->m_addressSender.to_string() + "\r\n");
         }
      }
      else if(m_estate == state_sender)
      {
         if(code == "250")
         {
            m_estate = state_recipient;
            print("RCPT TO: " + m_pemail->m_addressRecipient.to_string() + "\r\n");
         }
      }
      else if(m_estate == state_recipient)
      {
         if(code == "250")
         {
            m_estate = state_data;
            print("DATA\r\n");
         }
      }
      else if(m_estate == state_data)
      {
         if(code.Mid(0, 1) == "3")
         {
            m_estate = state_body;
            print("Subject:  =?utf-8?B?" + System.base64().encode(m_pemail->m_strSubject) + "?=\r\n");
            m_pemail->prepare_headers();
            print(m_pemail->m_strHeaders);
            print("Content-Type: text/plain; charset=\"utf-8\"\r\n");
            print("\r\n");
            string strBody = m_pemail->m_strBody;
            strBody.replace("\r\n", "\n");
            string_array stra;
            stra.add_tokens(strBody, "\n", TRUE);
            for(i32 i = 0; i < stra.get_count(); i++)
            {
               if(stra[i].Mid(0, 1) == ".")
               {
                  print("." + stra[i] + "\r\n");
               }
               else
               {
                  print(stra[i] + "\r\n");
               }
            }
            print(".\r\n");
         }
      }
      else if(m_estate == state_body)
      {
         if(code == "250")
         {
            m_estate = state_quit;
            print("QUIT\r\n");
         }
      }
      else if(m_estate == state_quit)
      {
         if(code == "221")
         {
            m_estate = state_end;
         }
      }
   }


} // namespace sockets

