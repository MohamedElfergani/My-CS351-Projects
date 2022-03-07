import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;
import javax.imageio.ImageIO;

public class ImageReader {

    public static void createImageFile(String string) throws IOException {
        try {
            File file = new File(string); // set the string with the file to type "file"
            Scanner scan = new Scanner(file); // scanner that takes the file

            try {
                // int to scan the width(x) of the binaries
                int x;
                x = scan.nextInt();
                // int to scan the height(y) of the binaries
                int y;
                y = scan.nextInt();
                scan.nextLine(); // continues to next line
                BufferedImage canvas = new BufferedImage(x, y, BufferedImage.TYPE_INT_RGB);

                //ints for width and height
                int currentHeight = 0;
                int currentWidth = 0;

                //while loop that takes scans that have next line
                while (scan.hasNextLine()) {
                    String currentLine = scan.nextLine(); // string that takes scan.nextLine()
                    Scanner scan2 = new Scanner(currentLine);
                    currentWidth = 0;
                    while (scan2.hasNext()) {
                        // string that takes a scanner and keeps looking for next lines
                        String rgbValue = scan2.next();
                        Scanner scan3 = new Scanner(rgbValue);
                        while (scan3.hasNext()) {
                            // new string named red that scans and uses delimiter with , because binaries
                            // are separated by ,
                            String red = scan3.useDelimiter(",").next();
                            red = Image.zerosToBinary(red);
                            int redValue = Integer.parseInt(red, 2) & 0xFF;

                            // new string named green that scans and uses delimiter with , because binaries
                            // are separated by ,
                            String green = scan3.useDelimiter(",").next();
                            green = Image.zerosToBinary(green);
                            int greenValue = Integer.parseInt(green, 2) & 0xFF;

                            // new string named blue that scans and uses delimiter with , because binaries
                            // are separated by ,
                            String blue = scan3.useDelimiter(",").next();
                            blue = Image.zerosToBinary(blue);
                            int blueValue = Integer.parseInt(blue, 2) & 0xFF;

                            int rgb = ((redValue << 16) | (greenValue << 8) | blueValue); 
                            canvas.setRGB(currentWidth, currentHeight, rgb);

                        }
                        if (currentWidth != x - 1) {
                            currentWidth++;
                        }
                        scan3.close();
                    }

                    if (currentHeight != y - 1) {
                        currentHeight++;
                    }
                    scan2.close();
                }

                ImageIO.write(canvas, "PNG", new File("output.png")); // generate output.png
                scan.close(); // close scan

            } catch (IOException e) {
                System.out.println("Error in writing image..."); // print when there is an error writing the image
            }
        } catch (FileNotFoundException e) {
            System.out.println("File not found..."); // print when the file was not found
        }
    }

    public static void main(String[] args) throws IOException {
        ImageReader.createImageFile("/Users/mohamedelfergani/Documents/GitHub/My-CS351-Assignments/question.dat");
    }

}