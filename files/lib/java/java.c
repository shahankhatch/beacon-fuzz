#include <stdio.h>
#include <jni.h>

JNIEnv* create_vm() {
	JavaVM* jvm;
	JNIEnv* env;
	JavaVMInitArgs args;
	JavaVMOption options[1];

	/* There is a new JNI_VERSION_1_4, but it doesn't add anything for the purposes of our example. */
	args.version = JNI_VERSION_1_8;
	args.nOptions = 1;
	options[0].optionString = "-Djava.class.path=/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-services-beaconchain-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-sync-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-networking-eth2-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-data-beaconrestapi-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-networking-p2p-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-services-powchain-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-services-chainstorage-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-validator-coordinator-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-ethereum-statetransition-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-services-serviceutils-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-data-metrics-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-data-recorder-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-validator-client-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-data-provider-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-data-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-storage-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-ethereum-datastructures-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-pow-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-util-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/tuweni-plumtree-0.9.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/tuweni-ssz-0.9.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/tuweni-rlpx-0.9.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/tuweni-crypto-0.9.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/tuweni-units-0.9.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jvm-libp2p-minimal-0.2.0-RELEASE.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/tuweni-kv-0.9.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/tuweni-rlp-0.9.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/tuweni-bytes-0.9.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/tuweni-config-0.9.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/milagro-crypto-java-0.4.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/metrics-core-1.3.4.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/tuweni-io-0.9.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/tuweni-concurrent-coroutines-0.9.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/tuweni-concurrent-0.9.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/mapdb-3.0.7.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/artemis-proto-0.8.2-SNAPSHOT.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/grpc-protobuf-1.25.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/kotlinx-coroutines-guava-1.1.1.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/grpc-stub-1.25.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/grpc-netty-shaded-1.25.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/grpc-core-1.25.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/grpc-protobuf-lite-1.25.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/grpc-api-1.25.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/guava-28.1-jre.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/log4j-slf4j-impl-2.12.1.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/log4j-core-2.12.1.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/gson-2.8.6.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/tuweni-toml-0.9.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/picocli-4.0.4.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/vertx-web-3.8.3.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/vertx-web-common-3.8.3.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/vertx-auth-common-3.8.3.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/vertx-core-3.8.3.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/log4j-api-2.12.1.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/plugin-api-1.3.4.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/failureaccess-1.0.1.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/listenablefuture-9999.0-empty-to-avoid-conflict-with-guava.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/perfmark-api-0.19.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jsr305-3.0.2.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/checker-qual-2.8.1.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/error_prone_annotations-2.3.3.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/j2objc-annotations-1.3.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/animal-sniffer-annotations-1.18.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/protobuf-java-3.10.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/reactor-core-3.3.0.RELEASE.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/bson4jackson-2.9.2.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/core-4.5.6.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/crypto-4.5.6.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jackson-databind-2.10.1.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/snappy-java-1.1.7.3.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/bcpkix-jdk15on-1.61.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/abi-4.5.6.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/rlp-4.5.6.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/utils-4.5.6.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/bcprov-jdk15on-1.64.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/quartz-2.3.2.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/commons-lang3-3.9.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/json-simple-1.1.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jackson-dataformat-yaml-2.10.1.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jnr-unixsocket-0.21.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jnr-enxio-0.19.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jnr-posix-3.0.47.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jnr-ffi-2.1.9.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/javalin-3.6.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/kotlin-stdlib-jdk8-1.3.31.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/kotlinx-coroutines-jdk8-1.1.1.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/kotlinx-coroutines-core-1.3.0-M1.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/logging-interceptor-3.8.1.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/okhttp-4.2.2.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/kotlin-stdlib-jdk7-1.3.31.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/okio-2.2.2.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/kotlin-stdlib-1.3.50.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/antlr4-runtime-4.7.1.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/netty-all-4.1.36.Final.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/commons-codec-1.13.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jaxb-api-2.3.1.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/netty-handler-proxy-4.1.42.Final.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/netty-codec-http2-4.1.42.Final.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/netty-codec-http-4.1.42.Final.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/netty-handler-4.1.42.Final.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/netty-resolver-dns-4.1.42.Final.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/netty-codec-socks-4.1.42.Final.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/netty-codec-dns-4.1.42.Final.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/netty-codec-4.1.42.Final.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/netty-transport-4.1.42.Final.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/netty-buffer-4.1.42.Final.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/netty-resolver-4.1.42.Final.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/netty-common-4.1.42.Final.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jackson-core-2.10.1.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/vertx-bridge-common-3.8.3.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/HikariCP-java7-2.4.13.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/slf4j-api-1.7.28.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/logl-api-0.3.1.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/rxjava-2.2.2.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/reactive-streams-1.0.3.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jackson-annotations-2.10.1.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/commons-math3-3.6.1.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/simpleclient_pushgateway-0.7.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/simpleclient_common-0.7.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/simpleclient_hotspot-0.7.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/simpleclient-0.7.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/tuples-4.5.6.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/Java-WebSocket-1.3.8.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/snakeyaml-1.24.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jffi-1.2.17.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jffi-1.2.17-native.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/asm-commons-5.0.3.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/asm-analysis-5.0.3.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/asm-util-5.0.3.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/asm-tree-5.0.3.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/asm-5.0.3.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jnr-a64asm-1.0.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jnr-x86asm-1.0.2.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/kotlin-stdlib-common-1.3.50.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/annotations-13.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/javax.activation-api-1.2.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/eclipse-collections-forkjoin-10.1.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/eclipse-collections-10.1.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/eclipse-collections-api-10.1.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/lz4-1.3.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/elsa-3.0.0-M5.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jetty-webapp-9.4.20.v20190813.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/websocket-server-9.4.20.v20190813.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jetty-servlet-9.4.20.v20190813.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jetty-security-9.4.20.v20190813.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jetty-server-9.4.20.v20190813.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jnr-constants-0.9.11.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/proto-google-common-protos-1.12.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/grpc-context-1.25.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/websocket-servlet-9.4.20.v20190813.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/javax.servlet-api-3.1.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/websocket-client-9.4.20.v20190813.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jetty-client-9.4.20.v20190813.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jetty-http-9.4.20.v20190813.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/websocket-common-9.4.20.v20190813.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jetty-io-9.4.20.v20190813.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jetty-xml-9.4.20.v20190813.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/annotations-4.1.1.4.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/opencensus-contrib-grpc-metrics-0.21.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/opencensus-api-0.21.0.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/jetty-util-9.4.20.v20190813.jar:/eth2/artemis-0.8.2-SNAPSHOT/lib/websocket-api-9.4.20.v20190813.jar:.";
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

	helloWorldClass = (*env)->FindClass(env, "tech/pegasys/artemis/statetransition/util/FuzzUtil"); //Hello

	mainMethod = (*env)->GetStaticMethodID(env, helloWorldClass, "main", "([Ljava/lang/String;)V");

	applicationArgs = (*env)->NewObjectArray(env, 1, (*env)->FindClass(env, "java/lang/String"), NULL);
	applicationArg0 = (*env)->NewStringUTF(env, "From-C-program");
	(*env)->SetObjectArrayElement(env, applicationArgs, 0, applicationArg0);

	(*env)->CallStaticVoidMethod(env, helloWorldClass, mainMethod, applicationArgs);

	testAttestationMethod = (*env)->GetStaticMethodID(env, helloWorldClass, "testAttestation", "([B[B)Z");


	char* bytes;
	int numBytes = 0;

	jbyteArray array_beaconstate = (*env)->NewByteArray(env, numBytes);
	(*env)->SetByteArrayRegion(env, array_beaconstate, 0, numBytes, (jbyte *) bytes);

  jbyteArray array_attestation = (*env)->NewByteArray(env, numBytes);
  (*env)->SetByteArrayRegion(env, array_attestation, 0, numBytes, (jbyte *) bytes);

  jboolean res = (*env)->CallStaticBooleanMethod(env, helloWorldClass, testAttestationMethod, array_beaconstate, array_attestation);
  printf("res:%d", res);

  testAttestationMethod2 = (*env)->GetStaticMethodID(env, helloWorldClass, "testAttestationRetState", "([B[B)[B");

  jarray res2 = (jarray) (*env)->CallStaticObjectMethod(env, helloWorldClass, testAttestationMethod2, array_beaconstate, array_attestation);
//  printf("res2:%d", res2);
}


int main(int argc, char **argv) {
	JNIEnv* env = create_vm();
	invoke_class( env );
}