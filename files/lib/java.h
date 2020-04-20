#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include <jni.h>


#include "base.h"

namespace fuzzing {

JNIEnv* create_vm() {
	JavaVM* jvm;
	JNIEnv* env;
	JavaVMInitArgs args;
	JavaVMOption options[1];

	/* There is a new JNI_VERSION_1_4, but it doesn't add anything for the purposes of our example. */
	args.version = JNI_VERSION_1_8;
	args.nOptions = 1;
	options[0].optionString = "-Djava.class.path=|CLASSPATH|:.";
	args.options = options;
	args.ignoreUnrecognized = JNI_FALSE;

	JNI_CreateJavaVM(&jvm, (void **)&env, &args);
	return env;
}


void invoke_class(JNIEnv* env) {
	jclass helloWorldClass;
	jmethodID mainMethod, testAttestationMethod, testAttestationMethod2;
	jobjectArray applicationArgs;
	jstring applicationArg0;

	helloWorldClass = env->FindClass("tech/pegasys/artemis/statetransition/util/FuzzUtil"); //Hello

	mainMethod = env->GetStaticMethodID(helloWorldClass, "main", "([Ljava/lang/String;)V");

	applicationArgs = env->NewObjectArray(1, env->FindClass("java/lang/String"), NULL);
	applicationArg0 = env->NewStringUTF("From-C-program");
	env->SetObjectArrayElement(applicationArgs, 0, applicationArg0);

	env->CallStaticVoidMethod(helloWorldClass, mainMethod, applicationArgs);

	testAttestationMethod = env->GetStaticMethodID(helloWorldClass, "testAttestation", "([B[B)Z");


	char* bytes;
	int numBytes = 0;

	jbyteArray array_beaconstate = env->NewByteArray(numBytes);
	env->SetByteArrayRegion(array_beaconstate, 0, numBytes, (jbyte *) bytes);

  jbyteArray array_attestation = env->NewByteArray(numBytes);
  env->SetByteArrayRegion(array_attestation, 0, numBytes, (jbyte *) bytes);

  jboolean res = env->CallStaticBooleanMethod(helloWorldClass, testAttestationMethod, array_beaconstate, array_attestation);
  printf("res:%d", res);

  testAttestationMethod2 = env->GetStaticMethodID(helloWorldClass, "testAttestationRetState", "([B[B)[B");

  jarray res2 = (jarray) env->CallStaticObjectMethod(helloWorldClass, testAttestationMethod2, array_beaconstate, array_attestation);
//  printf("res2:%d", res2);
}


class Java : public Base {
public:
Java(void) : Base() {
// instantiate the jvm and environemnt here
JNIEnv* env = create_vm();
	invoke_class( env );
};

std::optional<std::vector<uint8_t>> Run(
      const std::vector<uint8_t> &data) override {
      std::optional<std::vector<uint8_t>> ret = std::nullopt;

          if (data.empty()) {
            // Ensure data is not empty. Otherwise:
            //
            // "If size() is 0, data() may or may not return a null pointer."
            // https://en.cppreference.com/w/cpp/container/vector/data
            //
            // if nullptr, the pValue contains uninitialized data:
            // "If v is NULL, the contents of the bytes object are uninitialized."
            // https://docs.python.org/3/c-api/bytes.html?highlight=pybytes_check#c.PyBytes_FromStringAndSize
            return ret;
          }

          uint8_t* output;
          // copy return to 'output'
          ret.emplace(output, output + outputSize);

      // (data.data(), data.size())
      // convert the input vector of uint8_t into a java byte array
      // make the call to java here
      // perhaps take the class and the method names as parameters to dynamically configure for each test
      // convert the returned jarray into an optional vector of uint8_t
};

~Java();
};

} /* namespace fuzzing */