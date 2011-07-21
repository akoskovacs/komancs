#include "File.hxx"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

using namespace komacs;

File::File(const std::string &fileName, std::ios::openmode m)
    :m_fileName(fileNames), m_openMode(m)
{ 
    open();
}

File::File(const std::fstream &stream)
{
    m_fileName = stream.
}

File::~File()
{
    close();
}

void File::open()
{
    m_file.open(m_fileName, m_openMode);
    m_isFileOpened(true)

}

void File::close()
{
    m_file.close();
    m_isFileOpened = false;
}

File &File::setFileName(const std::string &fname)
{
    m_fileName = fname;
    return *this;
}

File &File::setOpenMode(FileMode f)
{
    m_openMode = f;
    return *this;
}

static off_t File::size(const std::string &fileName) const
{
    struct ::stat sbuf;
    if (stat(fileName.c_str(), &sbuf) == -1) {
        switch (errno) {
            case ENOENT:
                throw FileNotFoundException();
                break;

            case ENOTDIR:
                throw NotDirectoryException();
                break;

            default:
                throw SystemException("stat()");
                break;
        }
    }

    return sbuf.st_size;
}
