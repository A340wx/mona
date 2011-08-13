/*!
    \file   IOProcedures.cpp
    \brief

    Copyright (c) 2002-2007 Higepon.
    All rights reserved.
    License=MIT/X License

    \author  Higepon
    \version $Revision$
    \date   create:2007/07/14 update:$Date$
*/
#include <stdlib.h>
#include "procedures/Procedure.h"
#include "primitive_procedures.h"
#include "scheme.h"
#include "Nil.h"

//#include "Parser.h"
using namespace util;
using namespace std;
using namespace monash;

extern OutputPort* g_currentOutputPort;
extern OutputPort* g_defaultOutputPort;
extern InputPort*  g_defaultInputPort;
extern InputPort*  g_currentInputPort;

#include "dirent.h"

#ifdef USE_BOEHM_GC
class DirInfo :public gc
#else
class DirInfo
#endif
{
public:
    DirInfo(DIR* dir, ::util::String path) : dir(dir), path(path) {}
    DIR* dir;
    ::util::String path;
};

// full path only
PROCEDURE(MonaDirOpen, "mona-dir-open")
{
    ARGC_SHOULD_BE_BETWEEN(0, 1);
    ::util::String path;
    DIR* dir;
    if (ARGC == 0)
    {
        path = ".";
    }
    else
    {
        CAST(ARGV(0), SString, s);
        path = s->value();
    }
    if ((dir = opendir(path.data())) == NULL)
    {
        RAISE_ERROR(lineno(), "couldn't open dir: %s", path.data());
    }
    return new Variant(new DirInfo(dir, path), lineno());
}

//#include <monapi/io.h>

PROCEDURE(MonaDirRead, "mona-dir-read")
{
    ARGC_SHOULD_BE(1);
    CAST(ARGV(0), Variant, v);
    DirInfo* info = (DirInfo*)v->data();
    DIR* dir = info->dir;
    struct dirent* entry = readdir(dir);
    if (NULL == entry) return SCM_FALSE;
    SString* name = new SString(entry->d_name, lineno());
#ifdef MONA
    bool isDirectory = entry->d_type == ATTRIBUTE_DIRECTORY;
#else
    struct stat st;
    ::util::String target = info->path + "/" + entry->d_name;
    if (0 != stat(target.data(), &st))
    {
        RAISE_ERROR(lineno(), "couldn't read dir: %s", target.data());
    }
    bool isDirectory = S_ISDIR(st.st_mode);
#endif
    if (isDirectory)
    {
        return new Cons(name, SCM_TRUE, lineno());
    }
    else
    {
        return new Cons(name, SCM_FALSE, lineno());
    }
}

PROCEDURE(MonaDirClose, "mona-dir-close")
{
    ARGC_SHOULD_BE(1);
    CAST(ARGV(0), Variant, v);
    DirInfo* info = (DirInfo*)v->data();
    DIR* dir = info->dir;
    closedir(dir);
    return SCM_TRUE;
}

// PROCEDURE(MonLs, "mona-ls")
// {
//     ARGC_SHOULD_BE_BETWEEN(0, 1);
//     ::util::String path;
//     if (ARGC == 0)
//     {
//         path = ".";
//     }
//     else
//     {
//         CAST(ARGV(0), SString, s);
//         path = s->value();
//     }
//     DIR* dir;
//     struct dirent* entry;
//         SCM_TRACE_OUT("");
//     if ((dir = opendir(path.data())) == NULL)
//     {
//         SCM_TRACE_OUT("");
//         RAISE_ERROR(lineno(), "couldn't open dir: %s", path.data());
//     }

//     Objects* entries = new Objects;
//     for(entry = readdir(dir); entry != NULL; entry = readdir(dir))
//     {
//         entries->add(new SString(entry->d_name, lineno()));
//     }
//     ::monash::Cons* ret;
//     SCM_LIST(entries, ret, lineno());
//     closedir(dir);
//     return ret;
// }

PROCEDURE(TranscriptOn, "transcript-on")
{
    ARGC_SHOULD_BE(1);
    if (g_transcript != NULL)
    {
        RAISE_ERROR(lineno(), "already transcipt-on");
    }
    CAST(ARGV(0), SString, s);
    g_transcript = fopen(s->value().data(), "w+");
    if (NULL == g_transcript)
    {
        RAISE_ERROR(s->lineno(), "couldn't open output file: %s", s->value().data());
    }
    return SCM_UNDEF;
}


PROCEDURE(TranscriptOff, "transcript-off")
{
    ARGC_SHOULD_BE(0);
    if (g_transcript != NULL)
    {
        fclose(g_transcript);
        g_transcript = NULL;
    }
    return SCM_UNDEF;
}

PROCEDURE(FileExistsP, "file-exists?")
{
    ARGC_SHOULD_BE(1);
    CAST(ARGV(0), SString, s);
    FILE* f = fopen(s->value().data(), "r");
    if (f == NULL)
    {
        return SCM_FALSE;
    }
    else
    {
        fclose(f);
        return SCM_TRUE;
    }
}

PROCEDURE(CharReadyP, "char-ready?")
{
    ARGC_SHOULD_BE_BETWEEN(0, 1);
    InputPort* port;
    if (ARGC == 0)
    {
        port = g_currentInputPort;
    }
    else
    {
        CAST(ARGV(0), InputPort, p);
        port = p;
    }
    RETURN_BOOLEAN(port->charReady());
}

PROCEDURE(SetCurrentOutputPort, "set-current-output-port!")
{
    ARGC_SHOULD_BE(1);
    CAST(ARGV(0), OutputPort, p);
    g_currentOutputPort = p;
    return SCM_UNDEF;
}

PROCEDURE(SetCurrentInputPort, "set-current-input-port!")
{
    ARGC_SHOULD_BE(1);
    CAST(ARGV(0), InputPort, p);
    g_currentInputPort = p;
    return SCM_UNDEF;
}

PROCEDURE(InputPortP, "input-port?")
{
    ARGC_SHOULD_BE(1);
    RETURN_BOOLEAN(ARGV(0)->isInputPort());
}

PROCEDURE(OutputPortP, "output-port?")
{
    ARGC_SHOULD_BE(1);
    RETURN_BOOLEAN(ARGV(0)->isOutputPort());
}

PROCEDURE(EOFObjectP, "eof-object?")
{
    ARGC_SHOULD_BE(1);
    RETURN_BOOLEAN(ARGV(0)->isEof());
}

PROCEDURE(CloseInputPort, "close-input-port")
{
    ARGC_SHOULD_BE(1);
    CAST(ARGV(0), InputPort, p);
    p->close();
    return SCM_UNDEF;
}

PROCEDURE(CloseOutputPort, "close-output-port")
{
    ARGC_SHOULD_BE(1);
    CAST(ARGV(0), OutputPort, p);
    p->close();
    return SCM_UNDEF;
}

PROCEDURE(OpenOutputPort, "open-output-port")
{
    ARGC_SHOULD_BE(1);
    CAST(ARGV(0), SString, s);
    FILE* stream = fopen(s->value().data(), "w+");
    if (NULL == stream)
    {
        RAISE_ERROR(s->lineno(), "couldn't open output file: %s", s->value().data());
    }
    return new OutputPort(stream, lineno());
}

PROCEDURE(OpenInputPort, "open-input-port")
{
    ARGC_SHOULD_BE(1);
    CAST(ARGV(0), SString, s);
    FILE* stream = fopen(s->value().data(), "r");
    if (NULL == stream)
    {
        RAISE_ERROR(s->lineno(), "couldn't open input file: %s", s->value().data());
    }
    return new InputPort(s->value(), stream, lineno());
}

PROCEDURE(CurrentOutputPort, "current-output-port")
{
    ARGC_SHOULD_BE(0);
    return g_currentOutputPort;
}

PROCEDURE(CurrentInputPort, "current-input-port")
{
    ARGC_SHOULD_BE(0);
    return g_currentInputPort;
}

PROCEDURE(WriteChar, "write-char")
{
    ARGC_SHOULD_BE_BETWEEN(1, 2);
    OutputPort* port;
    if (ARGC == 1)
    {
        port = g_currentOutputPort;
    }
    else
    {
        CAST(ARGV(1), OutputPort, p);
        port = p;
    }
    CAST(ARGV(0), Charcter, c);
    port->writeCharacter(c);
    return SCM_UNDEF;
}

PROCEDURE(Read, "read")
{
    ARGC_SHOULD_BE_BETWEEN(0, 1);
    InputPort* port;
    if (ARGC == 0)
    {
        port = g_currentInputPort;
    }
    else
    {
        CAST(ARGV(0), InputPort, p);
        port = p;
    }
    Scanner* scanner = new Scanner(port, NULL, port);
    Parser parser(scanner);
    return parser.parse();
}

PROCEDURE(ReadChar, "read-char")
{
    ARGC_SHOULD_BE_BETWEEN(0, 1);
    InputPort* port;
    if (ARGC == 0)
    {
        port = g_currentInputPort;
    }
    else
    {
        CAST(ARGV(0), InputPort, p);
        port = p;
    }
    return port->readCharacter();
}

PROCEDURE(PeekChar, "peek-char")
{
    ARGC_SHOULD_BE_BETWEEN(0, 1);
    InputPort* port;
    if (ARGC == 0)
    {
        port = g_currentInputPort;
    }
    else
    {
        CAST(ARGV(0), InputPort, p);
        port = p;
    }
    return port->peekCharacter();
}

PROCEDURE(Write, "write")
{
    ARGC_SHOULD_BE_BETWEEN(1, 2);
    OutputPort* port;
    if (ARGC == 1)
    {
        port = g_currentOutputPort;
    }
    else
    {
        CAST(ARGV(1), OutputPort, p);
        port = p;
    }
    port->write(ARGV(0));
    return SCM_UNDEF;
}

PROCEDURE(NewLine, "newline")
{
    ARGC_SHOULD_BE_BETWEEN(0, 1);

    OutputPort* port;
    if (ARGC == 0)
    {
        port = g_currentOutputPort;
    }
    else
    {
        CAST(ARGV(0), OutputPort, p);
        port = p;
    }
#ifdef USE_MONA_GC
    port->display(new(false) Charcter('\n'));
#else
    port->display(new Charcter('\n'));
#endif
    return SCM_UNDEF;
}

PROCEDURE(Display, "display")
{
    ARGC_SHOULD_BE_BETWEEN(1, 2);
    OutputPort* port;
    if (ARGC == 1)
    {
        port = g_currentOutputPort;
    }
    else
    {
        CAST(ARGV(1), OutputPort, p);
        port = p;
    }
    port->display(ARGV(0));
    return SCM_UNDEF;
}

#if 0
uint8_t* loadFile(const String& path, uint32_t* size)
{
    uint8_t* buf;
    FILE* fp;

    fp = fopen(path.data(), "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "%s: file not found\n", __func__);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    *size = ftell(fp);

    if (size == 0)
    {
        fclose(fp);
        return NULL;
    }

    fseek(fp, 0, SEEK_SET);

    buf = new uint8_t [*size];
    if (buf == NULL)
    {
        fprintf(stderr, "%s: memory allocate error\n", __func__);
        fclose(fp);
        return NULL;
    }
    fread(buf, 1, *size, fp);
    fclose(fp);
    return buf;
}
#endif

PROCEDURE(Load, "load")
{
    ARGC_SHOULD_BE(1);
    CAST(ARGV(0), SString, s);

    // don't use env, use g_top_env instead !
#if 1
    Environment* environment = g_top_env;
    Object* port;
    SCM_APPLY1("open-input-port", environment, port, s);
    CAST(port, InputPort, inputPort);
    Scanner* scanner = new Scanner(inputPort, NULL, inputPort);
    Parser parser(scanner);
    for (Object* sexp = parser.parse(); sexp != SCM_EOF; sexp = parser.parse())
    {
//        logprintf("sexp=%s", (const char*)(sexp->toString().data()));
        Kernel::eval(sexp, env);
    }
    inputPort->close();
#else
    uint32_t size;
    uint8_t* buf = loadFile(s->value(), &size);
    buf[size - 1] = '\0';
    scheme_eval_string(String((char*)buf), env, false);
#endif
    return SCM_TRUE;
}
