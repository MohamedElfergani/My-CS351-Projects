public class Image {

    public static String zerosToBinary(String string) {
        String zeros = ""; // string named "zeros"
        // int named binaryLenght that takes the numbers of binary - a new string inside
        // the length
        int binaryLength = 8 - string.length();
        // while the length is more than or equal to 0
        for (int i = binaryLength; i >= 0; i--) {
            zeros += "0"; // addition assignment operator
        }
        zeros += string; // addition assignment operator
        return zeros; // return string 'zeros'
    }
}
