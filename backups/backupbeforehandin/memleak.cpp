
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <iostream>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <new>
#include <execinfo.h>
#include <stdio.h>
#include <regex.h>
#include <cxxabi.h>

using namespace std;



bool mem_trace = false;



#ifdef CS540_MEMTRACE



regex_t pat;

void comp_pat() __attribute__((constructor(101)));
void free_pat() __attribute__((destructor(101)));

void
comp_pat() {
    // This is the pattern for the system-supplied backtrace.
    const char *const pat_str =
     "^([^(]*\\()"// Before and including the left paren.
     "([^)+]*)" // Everything up to ) or +.
     "(.*)$"; // Everything after that.
    /*
    // This is the pattern for the backtrace in the code by Jeff Muizelaar.
    // String looks like: Element.cpp:55  _ZNK3xml7Element6acceptEPNS_7VisitorE()
    // Don't know whether or not there can be something in the parantheses.
    const char *const pat_str =
     "^([^[:space:]]+[[:space:]]+)" // Sequence of nonspace then space.
     "([[:alnum:]_]+)" // One or more identifier characters.
     "(\\(.*\\))$"; // Currently looks like ().
    */

    int ec = regcomp(&pat, pat_str, REG_EXTENDED); assert(ec == 0);
}

void
free_pat() {
    regfree(&pat);
}

void
stack_trace(size_t sz) {

    int ec;

    if (mem_trace) {

        fprintf(stderr, "Allocating %zu bytes, stack trace:\n", sz);

        // Grab the addresses.
        void *bt_buf[1000];
        int n = backtrace(bt_buf, 1000); assert(n >= 1);
        if (n == 1000) {
            fprintf(stderr, "    STACK TRACE TRUNCATED TO 1000!\n");
        }

        // Lookup the symbols.
        char **syms = backtrace_symbols(bt_buf, n); assert(syms != 0);

        // Now print out the stack, skip the first one, since it is
        // stack_trace() itself.
        for (int i = 1; i < n; i++) {

            // printf("symbol: %s\n", syms[i]);

            // First match is whole string, second is prefix, 3rd is mangled
            // name, 4th is suffix.
            regmatch_t matches[4];
            ec = regexec(&pat, syms[i], 4, matches, 0);

            if (ec == 0) {

                // If match succeeded, then demangle.

                regmatch_t &the_match(matches[2]); assert(the_match.rm_so != -1);
                size_t mangled_name_len =  the_match.rm_eo - the_match.rm_so;
                const char *mangled_name_begin = syms[i] + the_match.rm_so;
                char *mangled_name = (char *) malloc(mangled_name_len + 1);
                strncpy(mangled_name, mangled_name_begin, mangled_name_len);
                mangled_name[mangled_name_len] = '\0';
                //printf("mangled name: %s\n", mangled_name);

                // Demangle  extracted mangled name.
                const char *demangled_name = abi::__cxa_demangle(mangled_name, 0, 0, &ec);
                // Assume that it is either empty or C name.
                assert((ec == -2 && demangled_name == 0)
                 || (ec == 0 && demangled_name != 0));

                fprintf(stderr, "    %.*s\"%s\"%.*s\n",
                 matches[1].rm_eo - matches[1].rm_so, syms[i] + matches[1].rm_so,
                 // If demangling failed, just print the mangled name.
                 demangled_name ? demangled_name : mangled_name,
                 matches[3].rm_eo - matches[3].rm_so, syms[i] + matches[3].rm_so);

                free(mangled_name);
                free((void *) demangled_name);

            } else {

                // If match fails, just print the symbol as is.
                fprintf(stderr, "    %s\n", syms[i]);
            }
        }

        free(syms);
    }
}

void *
operator new(size_t sz) {
    stack_trace(sz);
    void *vp = malloc(sz);
    if (vp == 0) {
        throw std::bad_alloc();
    }
    return vp;
}

void *
operator new(size_t sz, const std::nothrow_t &) noexcept {
    stack_trace(sz);
    return malloc(sz);
}

void *
operator new[] (std::size_t sz) {
    stack_trace(sz);
    void *vp = malloc(sz);
    if (vp == 0) {
        throw std::bad_alloc();
    }
    return vp;
}

void *
operator new[] (std::size_t sz, const std::nothrow_t &) noexcept {
    stack_trace(sz);
    return malloc(sz);
}

void
operator delete(void *vp) noexcept {
    free(vp);
}
void
operator delete(void *vp, const std::nothrow_t &) noexcept {
    free(vp);
}
void operator delete(void *vp, std::size_t) {
    free(vp);
}

void
operator delete[](void *vp) noexcept {
    free(vp);
}
void
operator delete[] (void *vp, const std::nothrow_t &) noexcept {
    free(vp);
}
void
operator delete [](void *vp, std::size_t) {
    free(vp);
}


#endif

void goo() {
    new double;
}
void foo() {
    goo();
}

int
main() {

    mem_trace = true;
    new int;

    foo();
}