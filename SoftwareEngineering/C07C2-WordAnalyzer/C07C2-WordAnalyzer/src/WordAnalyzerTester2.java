/**
 * A test class for WordAnalyzer 
 * Source: https://horstmann.com/ 
 * Modified by Mark Baldwin
 * 
 */
public class WordAnalyzerTester2
{
   public static void main(String[] args)
   {
      test("mississippiii"); // expect: 4 (ss, ss, pp, iii)
      test("test"); // expect: 0 (no repeated letters)
      test("aabbcdaaaabb"); // expect: 4 (aa, bb, aaaa, bb)  
   }

   public static void test(String s)
   {
      WordAnalyzer wa = new WordAnalyzer(s);
      int result = wa.countRepeatedCharacters();
      System.out.println(result + " repeated characters.");
   }
}