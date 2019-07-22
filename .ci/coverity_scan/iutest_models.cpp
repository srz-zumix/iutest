namespace iutest
{

namespace internal
{

namespace posix
{

    void Abort()
    {
        __coverity_panic__();
    }

}

}

}
