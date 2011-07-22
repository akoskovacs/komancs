#ifndef FILE_HXX
#define FILE_HXX

#include "Exceptions.hxx"

#include <string>
#include <fstream>

#include <unistd.h>

namespace komancs {
    namespace errors {
        class komancs::File;
        class FileNotFoundException : public Exception
        {
        public:
            FileNotFoundException(const std::string &fname)
                : m_fileName(fname), Exception("File " + fname + " not found!")
            { }

            FileNotFoundException(const komancs::File &f)
                : m_fileName(f.fileName())
                , Exception("File " + f.fileName() + " not found!")
            { }

        private:
            std::string m_fileName;
        };
    }

    class File
    {
    public:
        enum AccessMode { Read = R_OK, Write = W_OK, Execute = X_OK, Exist = F_OK }
        File(const std::string &fileName
            , std::ios::openmode m = std::ios::read);
        File(const std::fstream &);
        ~File();

        void open();
        void close();

        File &setFileName(const std::string &);
        File &setOpenMode(FileMode);
        std::ios::openmode openMode() const { return m_openMode; }
        const std::string &fileName() const { return m_fileName; }
        std::fstream &stream() { return m_file; }
        off_t size() const { return size(m_fileName); }

        static bool isRegularFile(const std::string &) const;
        static bool isDirectory(const std::string &) const;
        static bool isExist(const std::string &) const;
        static bool isCapable(const std::string &, AccessMode);
        static off_t size(const std::string &) const;

    private:
        std::string m_fileName;
        std::ios::openmode m_openMode;
        std::fstream m_file;
        bool m_isFileOpened;
    };
}

#endif // FILE_HXX
