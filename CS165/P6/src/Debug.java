/* "Copyright (c) 2012-2016 by Fritz Sieker."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written
 * agreement is hereby granted, provided that the above copyright notice
 * and the following two paragraphs appear in all copies of this software,
 *
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE TO ANY PARTY FOR DIRECT,
 * INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE AUTHOR
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE AUTHOR SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS"
 * BASIS, AND THE AUTHOR NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT,
 * UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 */

import java.io.PrintStream;
import java.io.FileNotFoundException;
import java.lang.StackTraceElement;
import java.util.Arrays;

/**
 * In writing your code, you may be tempted to use {@code System.out.printf()}
 * to determine what is happening. As an alternative, the method
 * {@link #printf(String, Object...)} is provided. The nice thing about
 * {@link #printf(String, Object...)} in comparison to {@code System.out.printf()}
 * is that {@code Debug.printf()} <b>only</b> prints when debug is turn <b>on</b>.
 * <p>
 * You can turn debug on and off by setting the {@link #debugLevel} variable to non zero.
 * This is normally done by a command line parameter to the {@code main()}
 * of your program.  This module allows you to write debug code, but not need
 * to change your program in any way before turning it in.
 * <p>
 * If you use {@code System.out.printf()} you <b>MUST</b> either comment out the lines
 * or remove them before you submit your code for grading. This is a simple alternative
 * to the many logging packages that have more advanced capabilities. See
 * <a href="http://www.java-logging.com">this</a> page for examples.
 *
 * @author Fritz Sieker
 */

public class Debug  {

  /** Controls how much debug output is produced.
   * <p>
   * A value of 0 means no output. This is normally set by your program's {@code main()}
   * or by a command line argument. With the {@link #debugLevel} you can vary
   *  the amount of output from none, to a lot.
   */
  public static int debugLevel = 0;

  /** A variable to allow debug output to go someplace other than
   *  {@code System.err}. See the {@link #toFile(String)}, {@link #close()} methods.
   *  Default to {@code System.err}.
   */

  /** Define prefix of flag to turn on debuging */

  private static final String prefix = "-debug"; // use "-dbg" ???

  private static java.io.PrintStream ps = System.err;

  /** No instances, a purely static class */
  private Debug() {
  }

  /** This routine will set the {@link #debugLevel} from the arguments
   *  passed to {@code main()}. If the <b>first</b> argument is {@code -d} or
   *  {@code -dDigit}. the value will be used to initialize
   *  {@code debugLevel} and that argument will be removed.
   *  @param  args the array of arguments passed to {@code main}
   *  @return the {@code args} with the first value removed (if appropriate)
   */
  public static String[] init (String[] args) {
    if (args.length > 0) {
      String arg0 = args[0];

      if (arg0.startsWith(prefix)) {
        debugLevel = 1;
        int len = prefix.length();

        if (arg0.length() > len) { // look for level
          try {
            debugLevel = Integer.parseInt(arg0.substring(len));
          }
          catch (NumberFormatException nfe) {
            System.err.printf("Bad debug specifier '%s'\n", arg0);
            System.exit(-1);
          }
        }

        int newLen = args.length - 1;
        String[] newArgs = new String[newLen];
        System.arraycopy(args, 1, newArgs, 0, newLen);
        args = newArgs;
      }
    }

    return args;
  }

  /** Print the output prefix "DEBUG fileName[lineNumber] methodName"
   * @param format  the format string for the output
   * @param args  arguments for the format string (variable number)
   */
  private static void printIt (String format, Object ... args) {
    StackTraceElement ste = (new Throwable()).getStackTrace()[2];

    String msg = String.format("DEBUG %s[%d] %s() %s\n", ste.getFileName(),
                               ste.getLineNumber(), ste.getMethodName(),
                               Debug.format(format, args));

    System.out.flush();
    ps.print(msg); // "\n" in msg outputs single value (ps.println() is two)
    ps.flush();
  }

  /** An "extension" of {@link String#format(String, Object...)}. Automatically converts
   *  arrays to Strings using the {@code Arrays.toString()} methods.
   *  Arrays of arrays are also handled. The argument list is exactly the same
   *  as that of {@code String.format()}, so any of the features of that
   *  code may be used. If there is only a <b>single</b> argument after the
   *  format and if that argument is an array, cast it to an Object using
   *  {@code (Object)}
   *  @param format the format string for the output (use {@code %s} for arrays)
   *  @param args arguments for the format string (variable number)
   *  @return the formatted string with all array objects expanded
   */
  public static String format (String format, Object ... args) {
    for (int i = 0; i < args.length; i++) {
      if ((args[i] != null) && args[i].getClass().isArray()) {
        if (args[i] instanceof boolean[])
          args[i] = Arrays.toString((boolean[]) args[i]);
        else if (args[i] instanceof byte[])
          args[i] = Arrays.toString((byte[]) args[i]);
        else if (args[i] instanceof char[])
          args[i] = Arrays.toString((char[]) args[i]);
        else if (args[i] instanceof double[])
          args[i] = Arrays.toString((double[]) args[i]);
        else if (args[i] instanceof float[])
          args[i] = Arrays.toString((float[]) args[i]);
        else if (args[i] instanceof int[])
          args[i] = Arrays.toString((int[]) args[i]);
        else if (args[i] instanceof long[])
          args[i] = Arrays.toString((long[]) args[i]);
        else if (args[i] instanceof Object[])
          args[i] = Arrays.deepToString((Object[]) args[i]);
        else if (args[i] instanceof short[])
          args[i] = Arrays.toString((short[]) args[i]);
      }
    }
    return String.format(format, args);
  }

  /** Simple routine to print the fileName, lineNumber and methodName. Used
   *  for quick debugging to see if your code even gets to a particular place.
   * @return always returns {@code true}. Allows you to "abuse" the
   * {@code assert} statement for high performance.
   */
  public static boolean HERE () {
    if (debugLevel != 0)
      printIt("HERE");

    return true;
  }

  /** Print a message if the variable {@link #debugLevel} is non-zero.
   * <p>
   * The argument list is exactly the same as that of
   * {@link String#format(String, Object...)}, so any of the features of
   * that code may be used. See the documentation of
   * {@link #format(String, Object...)} for details on printing arrays.
   * @param format  the format string for the output
   * @param args  arguments for the format string (variable number)
   * @return always returns {@code true}. Allows you to "abuse" the
   *         {@code assert} statement for high performance.
   */
  public static boolean printf (String format, Object ... args) {
    if (debugLevel != 0)
      printIt(format, args);

    return true;
  }

  /** Print a message if the parameter {@code level} is less than or equal to
   *  {@link #debugLevel}.
   *  <p>
   * The argument list following {@code level}
   * is exactly the same as that of {@link String#format(String, Object...)},
   * so any of the features of that code may be used. See the documentation of
   * {@link #format(String, Object...)} for details on printing arrays.
   * @param level  controls whether message is printed or not
   * @param format  the format string for the output
   * @param args  arguments for the format string (variable number)
   * @return always returns {@code true}. Allows you to "abuse" the
   *         {@code assert} statement for high performance.
   */
  public static boolean printf (int level, String format, Object ... args) {
    if (level <= debugLevel)
      printIt(format, args);

    return true;
  }

  /** Send debugging output to a file.
   * @param fileName name of the file to send output to
   * @throws FileNotFoundException if unable to access the file
   */

  public static void toFile (String fileName) throws FileNotFoundException {
    close();
    ps = new PrintStream(fileName);
  }

  /** Close the output stream if it is not {@link System#err}. For use in
   *  conjunction with {@link #toFile(String)}
   */
  public static void close () {
    if (ps != System.err) {
      ps.close();
      ps = System.err;
    }
  }
}
