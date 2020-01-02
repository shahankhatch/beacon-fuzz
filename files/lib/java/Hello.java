class Hello {
//  public native void sayHello();

//  static { System.loadLibrary("hellolib"); }

  public static void main(String[] args){
    Hello h = new Hello();
    h.sayHello(args[0]);
  }

  public void sayHello(String h) {
    System.out.println("hi:"+h+":");
  }
}