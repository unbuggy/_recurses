# Recurses

The Recurses library is a C++ wrapper around [NCurses][].  The goals are to insulate NCurses' liberal use of preprocessor macros, to avoid pollution of the global namespace, and to support C++ idioms, including RAII.

[NCurses]: TODO

Note that NCurses already defines its own C++ interface, which (like Recurses) limits the use of macros and presents a class-based interface to the library.  The NCurses C++ interface has the advantage of being maintained alongside the C codebase, and can inline more functions than a mere wrapper like Recurses;  however, the native interface suffers severe drawbacks:

* The code predates C++ ISO standardization, and its age shows; for example, all classes and most functions are declared at global scope.  (Backward compatibility with obsolescent systems would likely hamper any attempt to use C++ features introduced in recent decades.)

* As of this writing, the code is rejected by popular compilers because of incorrect pointer type declarations.  (Fixing them is straight-forward: In a few places, declarations of the form `NSomeType parameter[]` must be changed to `NSomeType* parameter[]`.)

* The code is of uneven quality.  Consider the window assignment operator:

        NCursesWindow& operator=(const NCursesWindow& rhs)
        {
          if (this != &rhs)
            *this = rhs;
          return *this;
        }
    
    As the recursive call to `operator=` has no base case, the behavior is undefined.  On my current workstation, the result is `SIGSEGV`.

* The NCurses C++ interface directly includes raw C headers, then attempts to transform the result into something usable from C++; for example:

        /* these names conflict with STL */
        #undef box
        #undef clear
        #undef erase
        #undef move
        #undef refresh

    While the library appears to be very thorough, and the `configure` script even sports an experimental `--disable-macros` option, such a piecemeal approach will always be at a disadvantage relative to a wrapper that completely insulates the underlying library.  Recurses never includes NCurses headers in any of its own public header files, and thus never pollutes its own clients' namespaces.
