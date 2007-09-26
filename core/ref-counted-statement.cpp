//
// Copyright (C) 2004-2007 Maciej Sobczak, Stephen Hutton
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#define SOCI_SOURCE
#include "ref-counted-statement.h"
#include "session.h"

using namespace soci;
using namespace soci::details;

void ref_counted_statement::final_action()
{
    try
    {
        st_.alloc();
        st_.prepare(session_.get_query_stream().str(), eOneTimeQuery);
        st_.define_and_bind();
        st_.execute(true);
    }
    catch (...)
    {
        st_.clean_up();
        throw;
    }

    st_.clean_up();
}

std::ostringstream & ref_counted_statement_base::get_query_stream()
{
    return session_.get_query_stream();
}