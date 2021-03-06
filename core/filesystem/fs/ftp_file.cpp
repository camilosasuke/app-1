#include "framework.h"
#include "apex/filesystem/fs/_fs.h"
#include "core/net/ftp/_.h"
#include "ftp_file.h"



ftpfs_file::ftpfs_file(::ftpfs * pftp, ::ftp::client_socket * pclient) 
{

   m_pftp = pftp;

   m_pclient = pclient;

   m_varFile = Context.file().time(Context.dir().time());

}


void ftpfs_file::close()
{

   try
   {

      m_pfile->close();

   }
   catch(...)
   {


   }

   m_pfile.release();

   ::ftp::client_socket * pclient = m_pclient;

   int iTry = 0;

retry:

   if (iTry > 0)
   {

      m_pftp->defer_initialize(&pclient, m_filepath);

   }


   if (pclient->m_estate != ::ftp::client_socket::state_logged)
   {

      if (iTry > 3)
      {

         return;

      }

      iTry++;

      goto retry;

   }

   string strRemoteFile = System.url().get_object(m_filepath);

   if (!pclient->UploadFile(m_varFile, strRemoteFile))
   {

      if (iTry > 3)
      {

         return;

      }

      pclient->m_estate = ::ftp::client_socket::state_initial;

      iTry++;

      goto retry;

   }


}

ftpfs_file::~ftpfs_file()
{


}


::status::result ftpfs_file::open(const ::file::path & filepath, const efileopen & eopen)
{

   m_filepath = filepath;

   return m_pfile->open(m_varFile, ::file::mode_create | ::file::type_binary | ::file::mode_read_write | ::file::defer_create_directory);

}


memsize ftpfs_file::read(void *pdata, memsize nCount)

{

   return m_pfile->read(pdata, nCount);


}


void ftpfs_file::write(const void * pdata, memsize nCount)

{

   m_pfile->write(pdata, nCount);


}


filesize ftpfs_file::get_size() const
{

   return m_pfile->get_size();

}


filesize ftpfs_file::seek(filesize lOff, ::file::e_seek nFrom)
{

   return m_pfile->seek(lOff, nFrom);

}


