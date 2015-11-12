# ofxSimpleOscSender

i wanna send with `send("/address", foo, bar, buzz)`

## Dependencies

* ofxOsc

this addon uses C++11

## API

### ofxSimpleOscSender

* void send(const std::string &address, const Args & ... args);
	* Args : `arithmetic`, `string`, `ofBuffer`

and all `ofxOscSender`'s public method


### ofxMultiOscSender

* void send(const std::string &address, const Args & ... args);
	* same as ofxSimpleOscSender::send
* void addTarget(const std::string &host, int port);
* void removeTarget(const std::string &host, int port);

and all `ofxOscSender`'s public method

## Update history

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
