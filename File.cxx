#include "Exceptions.hxx"
#include "File.hxx"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include <fstream>

using namespace komacs;

namespace {
    struct stat getStat(const std::string &);
}

File::File(const std::string &fileName, std::ios::openmode m)
    :m_fileName(fileName), m_openMode(m)
{  open(); }

File::File(const std::fstream &stream)
    : m_fileName(stream.name())
{ }

File &File::open()
{
    m_file.open(m_fileName, m_openMode);
    m_isFileOpened(true);
    return *this;
}

File &File::close()
{
    if (m_isFileOpened) {
        m_file.close();
        m_isFileOpened = false;
    }
    return *this;
}

File &File::setFileName(const std::string &fname)
{
    m_fileName = fname;
    close();
    return *this;
}

File &File::setOpenMode(std::ios::openmode mode)
{
    m_openMode = mode;
    close();
    return *this;
}

off_t File::size(const std::string &fileName) const
{
    return getStat(fileName).st_size;
}

bool File::isRegularFile(const std::string &fileName) const
{
    return (bool)S_ISREG(getStat(fileName).st_mode);
}

bool File::isDirectory(const std::string &fileName) const
{
    return (bool)S_ISDIR(getStat(fileName).st_mode);
}

bool File::isExist(const std::string &fileName) const
{
    return isCapable(fileName, Exist);
}

bool File::isCapable(const std::string &fileName, AccessMode m) const
{
    if (access(fileName.c_str(), m) == -1) {
        switch (errno) {
            case EACCES:
                return false;
                break;

            case ENOENT:
                throw error::FileNotFoundException();
                break;

            default:
                throw error::SystemException("access()");
                break;
        }
    }
    return true;
}

struct stat getStat(const std::string &fileName)
{
    const char *fname = fileName.c_str();
    struct ::stat sbuf;
    if (stat(fname, &sbuf) == -1) {
        switch (errno) {
            case ENOENT:
                throw error::FileNotFoundException();
                break;

            default:
                throw error::SystemException("stat()");
                break;
        }
    }
    return sbuf;
}
