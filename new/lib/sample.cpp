#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

using namespace rapidjson;
using namespace std;

int main()
{

    StringBuffer w;

    Writer<StringBuffer> writer(w);

    std::cout << "Example_Output : Using Writer() Function \n\t";

    /* Here Between StartObject() and EndObject() using Writer we write key-value code to print*/

    writer.StartObject();

    writer.Key("This is key");

    writer.String("This is value of key(using .String)");

    writer.Key("True value(using.Boolean)");

    writer.Bool(true);

    writer.EndObject();

    cout << w.GetString() << endl;

    return 0;
}