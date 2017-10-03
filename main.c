       #include <stdio.h>
       #include <stdlib.h>
       #include <dlfcn.h>
       #include <gnu/lib-names.h>  /* Defines LIBM_SO (which will be a
                                      string such as "libm.so.6") */
       int
       main(int argc, char *argv[])
       {
           void *handle;
           void (*foo)(void);
           char *error;

           handle = dlopen(argv[1], RTLD_LAZY);
           if (!handle) {
               fprintf(stderr, "%s\n", dlerror());
               exit(EXIT_FAILURE);
           }

           dlerror();    /* Clear any existing error */

           foo = (void (*)(void)) dlsym(handle, "foo");

           /* According to the ISO C standard, casting between function
              pointers and 'void *', as done above, produces undefined results.
              POSIX.1-2003 and POSIX.1-2008 accepted this state of affairs and
              proposed the following workaround:

                  *(void **) (&cosine) = dlsym(handle, "cos");

              This (clumsy) cast conforms with the ISO C standard and will
              avoid any compiler warnings.

              The 2013 Technical Corrigendum to POSIX.1-2008 (a.k.a.
              POSIX.1-2013) improved matters by requiring that conforming
              implementations support casting 'void *' to a function pointer.
              Nevertheless, some compilers (e.g., gcc with the '-pedantic'
              option) may complain about the cast used in this program. */

           error = dlerror();
           if (error != NULL) {
               fprintf(stderr, "%s\n", error);
               exit(EXIT_FAILURE);
           }

           foo();
           dlclose(handle);
           exit(EXIT_SUCCESS);
       }
