# ofxSmartOscSender

i wanna send with `send("/address", foo, bar, buzz)`

## Dependencies

* ofxOsc

this addon uses C++11

## API

### ofxSmartOscSender

* void send(const std::string &address, const Args & ... args);
	* `Args` : arithmetic type, `string`, `ofBuffer`

default mode is use `sendAsSimpleFormat`.
you can change to use `sendAsStrictFormat` with `setUsingStrictFormat(true);`.

* void sendAsStrictFormat(const std::string &address, const Args & ... args);

send arithmetic type as following mapping.

| arg type        | osc type |
|:----            |:----     |
| integral        | int32    |
| floating points | float    |

* void sendAsSimpleFormat(const std::string &address, const Args & ... args);

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

* void setUsingStrictFormat(bool bStrict);
* bool getUsingStrictFormat() const;

* void setSendingWithWrapInBundle(bool wrapInBundle);
* bool getSendingWithWrapInBundle() const;

* and all `ofxOscSender`'s public method

### ofxMultiOscSender

* void addTarget(const std::string &host, int port);
* void removeTarget(const std::string &host, int port);

* and all `ofxSmartOscSender`'s public method

### extend operator<< of ofxOscMessage

you can extend with `using namespace using namespace bbb::ofxOscMessageStreamOperators;`

#### ex.

```
	ofxOscMessage m;
	m.setAddress("/address");
	m << 1 << "hoge" << 14.0f;
	// means:
	// m.addInt32Arg(1);
	// m.addString("hoge");
	// m.addFloatArg(14.0f);
```

see: *ofxOscMessageStreamOperator.h*

## Update history

### 2015/11/14 ver 0.0.2 release

* renamed from `ofxSimpleOscSender` (suggested from [yusuketomoto](https://github.com/yusuketomoto))
* add `set/getUsingStrictFormat`, `set/getSendingWithWrapInBundle`
* extend `operator<<` for `ofxOscMessage` in **ofxOscMessageStreamOperator.h**. (idea from [satoruhiga](https://github.com/satoruhiga))

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
