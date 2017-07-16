/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Fabien
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <iostream>
#include <cassert>

#include "../version.h"

using namespace std;

int main()
{
    assert(Version("1.0.0") > Version("0.2.3-test+meta"));
    assert(Version("1.2.3") < Version("1.2.100"));
    assert(Version("1.2.3-alpha") < Version("1.2.3-beta"));
    assert(Version("1.2.3-alpha") < Version("1.2.3-alphaa"));
    assert(Version("1.2.3-alpha.alpha.1") < Version("1.2.3-alpha.alpha"));
    assert(Version("1.2.3-alpha.alpha.1") < Version("1.2.3-beta"));
    assert(Version("1.2.6-alpha.2") == Version("1.2.6-alpha.2"));
    assert(Version("1.2.6-alpha.2+meta") == Version("1.2.6-alpha.2+different.meta"));

    assert(Version("1.2.3-45") > Version("1.2.3-9"));
    assert(Version("1.2.3-45") < Version("1.2.3-alpha"));
    assert(!(Version("1.2.3-alpha") < Version("1.2.3-12")));
    assert(Version("1.2.3-45") < Version("1.2.3-45a"));

    assert(!(Version("1.2.3").compatible("5.2.3")));
    assert(Version("1.2.3").compatible("1.1.25"));
    assert(!(Version("1.12.5").compatible("1.13.25")));

    {
        Version v("1.2.555-alpha.pre.5+meta.buildtime.123456");
        assert(v.major() == 1);
        assert(v.minor() == 2);
        assert(v.patch() == 555);
        assert(v.prerelease() == "alpha.pre.5");
        assert(v.prereleaseIdentifiers().size() == 3);
        assert(v.prereleaseIdentifiers()[0] == "alpha");
        assert(v.prereleaseIdentifiers()[1] == "pre");
        assert(v.prereleaseIdentifiers()[2] == "5");
        assert(v.metadata() == "meta.buildtime.123456");
    }

    {
        Version v("15.23.555-alpha.pre.5");
        assert(v.major() == 15);
        assert(v.minor() == 23);
        assert(v.patch() == 555);
        assert(v.prerelease() == "alpha.pre.5");
        assert(v.prereleaseIdentifiers().size() == 3);
        assert(v.prereleaseIdentifiers()[0] == "alpha");
        assert(v.prereleaseIdentifiers()[1] == "pre");
        assert(v.prereleaseIdentifiers()[2] == "5");
        assert(v.metadata() == "");
    }

    {
        Version v("1.2.555+meta.buildtime.123456");
        assert(v.major() == 1);
        assert(v.minor() == 2);
        assert(v.patch() == 555);
        assert(v.prerelease() == "");
        assert(v.metadata() == "meta.buildtime.123456");
    }

    cout << "Success !" << endl;
    return 0;
}
