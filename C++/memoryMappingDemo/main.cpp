#include <algorithm>
#include <iostream>
#include <cstring>

// for mmap:
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

using namespace std;

const char* map_file(const char* fname, size_t& length);
void handle_error(const char* msg);
static uintmax_t wc(char const *fname);

int main() {
    size_t length;
    const char *f = map_file("/Users/j/Desktop/wp.txt", length);
    const char *l = f + length;

    uintmax_t m_numLines = 0;
    while (f && f!=l)
        if ((f = static_cast<const char*>(memchr(f, '\n', l-f))))
            ++m_numLines, ++f;

    std::cout << "m_numLines = " << m_numLines << "\n";
}

void handle_error(const char* msg) {
    perror(msg);
    exit(255);
}

const char* map_file(const char* fname, size_t& length) {
    int fd = open(fname, O_RDONLY);
    if (fd == -1)
        handle_error("open");

    // obtain file size
    struct stat sb;
    if (fstat(fd, &sb) == -1)
        handle_error("fstat");

    length = sb.st_size;

    const char* addr = static_cast<const char*>(mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0u));
    if (addr == MAP_FAILED)
        handle_error("mmap");

    // TODO close fd at some point in time, call munmap(...)
    return addr;
}

// Using boost
//#include <boost/iostreams/device/mapped_file.hpp> // for mmap
//#include <algorithm>  // for std::find
//#include <iostream>   // for std::cout
//#include <cstring>

//int main() {
//    boost::iostreams::mapped_file mmap("input.txt", boost::iostreams::mapped_file::readonly);
//    auto f = mmap.const_data();
//    auto l = f + mmap.size();

//    uintmax_t m_numLines = 0;
//    while (f && f!=l)
//        if ((f = static_cast<const char*>(memchr(f, '\n', l-f))))
//            m_numLines++, f++;

//    std::cout << "m_numLines = " << m_numLines << "\n";
//}

/**
 * The last bit of performance I could squeeze out of this I found by looking at the source of GNU
 * coreutils wc. To my surprise using the following (greatly simplified) code adapted from wc runs
 * in about 84% of the time taken with the memory mapped file above:
 */
static uintmax_t wc(char const *fname) {
    static const auto BUFFER_SIZE = 16*1024;
    int fd = open(fname, O_RDONLY), check;
    if(fd == -1)
        handle_error("open");

    /* Advise the kernel of our access pattern.  */
//    check = posix_fadvise(fd, 0, 0, 1);  // FDADVICE_SEQUENTIAL
//    if(check)
//        handle_error("posix");

    char buf[BUFFER_SIZE + 1];
    uintmax_t lines = 0;

    while(size_t bytes_read = read(fd, buf, BUFFER_SIZE)) {
        if(bytes_read == (size_t)-1)
            handle_error("read failed");
        if (!bytes_read)
            break;

        for(char *p = buf; (p = (char*) memchr(p, '\n', (buf + bytes_read) - p)); ++p)
            ++lines;
    }

    return lines;
}
