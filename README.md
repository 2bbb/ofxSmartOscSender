# ofxSmartOscSender

i wanna send with `send("/address", foo, bar, buzz)`

## Notice

this addon uses C++11, require of0.9.0~

if you use master branch and causes an error, please pull latest commit.

## Dependencies

* ofxOsc

## API

### ofxSmartOscSender

#### sending OSC

* void send(const std::string &address, const Args & ... args);
	* `Args` : arithmetic type, `string`, `ofBuffer`

default mode is use `sendAsSimpleFormat`.
you can change to use `sendAsStrictFormat` with `setUsingStrictFormat(true);`.

* void sendAsSimpleFormat(const std::string &address, const Args & ... args);

send arithmetic type as following mapping.

| arg type        | osc type |
|:----            |:----     |
| integral        | int32    |
| floating points | float    |

* void sendAsStrictFormat(const std::string &address, const Args & ... args);

send arithmetic type as following mapping.

| arg type           | osc type |
|:----               |:----     |
| bool               | bool     |
| char               | char     |
| unsigned char      | int32    |
| short              | int32    |
| unsigned short     | int32    |
| int                | int32    |
| unsigned int       | int64    |
| long               | int64    |
| unsigned long      | int64    |
| long long          | int64    |
| unsigned long long | int64    |
| float              | float    |
| double             | double   |

#### stream operator

* ofxSimpleOscSender &operator<<(Type t)

add osc argument that allowed type.

argument follows rule as strict/simple mapping is gave by [`setUsingStrictFormat`](#option_setting).

* ofxSimpleOscSender &operator<<(Terminator &t)

only allow `bbb::send`.

##### example.

```cpp
	ofxOscSender sender;
	...
	sender("/address") << 1 << 2 << bbb::send;
	sender << 1 << 2 << bbb::send("/address"); // same as above!
	sender("/hogehoge") << 1 << 2 << bbb::send("/address"); // overwrite address with argument of send. so, same as above!
```

#### <a name="option_setting">option setting</a>

* void setUsingStrictFormat(bool bStrict);
* bool getUsingStrictFormat() const;

default is `false`.

if you want to use OSC with Cycling'74 Max, you should be use `setUsingStrictFormat(false)` (so it is default!).

* void setSendingWithWrapInBundle(bool wrapInBundle);
* bool getSendingWithWrapInBundle() const;

default is `true`.

* and all `ofxOscSender`'s public method

### ofxMultiOscSender

* void addTarget(const std::string &host, int port);
* void removeTarget(const std::string &host, int port);

* and all `ofxSmartOscSender`'s public method

### extend operator<< of ofxOscMessage

you can extend with

```cpp
using namespace using namespace bbb::ofxOscMessageStreamOperators;
using namespace using namespace bbb::ofxOscMessageStrictStreamOperators;
using namespace using namespace bbb::ofxOscMessageSimpleStreamOperators;
```

`ofxOscMessageStreamOperators` is alias of `ofxOscMessageSimpleStreamOperators`.

if you want to use OSC with Cycling'74 Max, you should be use `ofxOscMessageSimpleStreamOperators`

#### example.

```cpp
	ofxOscMessage m;
	m.setAddress("/address");
	m << 1 << "hoge" << 14.0f;
	// means:
	// m.addInt32Arg(1);
	// m.addString("hoge");
	// m.addFloatArg(14.0f);
```

see: *ofxOscMessageStreamOperator.h*

### extend operator<<(std::ostream, const ofxOscMessage &)

you will get `ofLogNotice() << m;` with `#include <ofxOscMessageOstreamExtention.h>`

### ofxOscMessageInputStream (has operator>>)

```cpp
ofxOscMessageInputStream(m) >> x >> y >> str;
oscin(m) >> x >> y >> str; // same above
```

or

```cpp
oscin in(m);
in >> x;
in >> y;
in >> str;
```

## Update history

### 2016/03/15 ver 0.0.6 release

* fix problem: duprecated symbol
* fix simple mistake about README. omg...

### 2016/01/04 ver 0.0.5 release

* add `ofxOscMessageInputStream.h`

### 2015/11/16 ver 0.0.4 release

* add `ofxOscMessageOstreamExtention.h`

### 2015/11/15 ver 0.0.3 release

* fix wrong namespace alias
* add stream operator for ofxSimpleOscSender/ofxMultiOscSender
* tiny bugifxes

### 2015/11/14 ver 0.0.2 release

* renamed from `ofxSimpleOscSender` (suggested from [yusuketomoto](https://github.com/yusuketomoto))
* add `set/getUsingStrictFormat`, `set/getSendingWithWrapInBundle`
* extend `operator<<` for `ofxOscMessage` in **ofxOscMessageStreamOperator.h**. (idea from [satoruhiga](https://github.com/satoruhiga))
* add example

### 2015/11/12 ver 0.0.1 release

* initial

## License

MIT License.

## Author

* ISHII 2bit [bufferRenaiss co., ltd.]
* ishii[at]buffer-renaiss.com

## At the last

Please create a new issue if there is a problem.
And please throw a pull request if you have a cool idea!!
