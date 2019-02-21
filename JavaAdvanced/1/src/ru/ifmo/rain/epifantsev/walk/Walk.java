package ru.ifmo.rain.epifantsev.walk;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.InvalidPathException;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Walk {

    private static final int LENGTH_OF_ARGUMENTS = 2;
    private static final int BLOCK_SIZE = 1024;
    private static final int HASH_VALUE = 0x811c9dc5;
    private static final int FNV_32_PRIME = 0x01000193;
    private static final int ERROR_ZERO = 0x00000000;

    public static void main(String[] args) {
        if (args == null || args.length != LENGTH_OF_ARGUMENTS || args[0] == null || args[1] == null) {
            System.err.println("Wrong input. Please, use: <InputFilePath>, <OutputFilePath>");
            return;
        }

        Path pathInput, pathOutput;
        try {
            pathInput = Paths.get(args[0]);
        } catch (InvalidPathException e) {
            System.err.println("File name for Input contains forbidden characters" + e.getMessage()) ;
            return;
        }

        try {
            pathOutput = Paths.get(args[1]);
        } catch (InvalidPathException e) {
            System.err.println("File name for Output contains forbidden characters" + e.getMessage());
            return;
        }

        try {
            if (pathOutput.getParent() != null) {
                Files.createDirectories(pathOutput.getParent());
            }
        } catch (IOException e) {
            System.err.println("Can't create output file by path" + e.getMessage());
        }

        String fileName;

        try (BufferedReader reader = Files.newBufferedReader(pathInput, StandardCharsets.UTF_8)) {
            try ( BufferedWriter writer = Files.newBufferedWriter(pathOutput, StandardCharsets.UTF_8)) {
                while ((fileName = reader.readLine()) != null) {
                    writer.write(String.format("%08x %s", getHashSum(fileName), fileName) + System.lineSeparator());
                }
            } catch (FileNotFoundException e) {
                System.err.println("Exception throws, because reading file not found" + e.getMessage());
            } catch (IOException e) {
                System.err.println("Exception throws, when reading file" + e.getMessage());
            }
        } catch (FileNotFoundException e) {
            System.err.println("Exception throws, because writing file not found" + e.getMessage());
        } catch (IOException e) {
            System.err.println("Exception throws, when writing file" + e.getMessage());
        }
    }

    private static int hash(final byte[] bytes, final int count, int hash) {
        for (int i = 0; i < count; ++i) {
            int b = bytes[i] & 0xff;
            hash *= FNV_32_PRIME;
            hash ^= b;
        }
        return hash;
    }

    private static int getHashSum(final String fileName) {
        Path path;

        try {
            path = Paths.get(fileName);
        } catch (InvalidPathException e) {
            System.err.println("The file name contains forbidden characters, file name: " + fileName + " " + e.getMessage());
            return ERROR_ZERO;
        }

        byte[] bytes = new byte[BLOCK_SIZE];
        int result = HASH_VALUE, bytesRead;

        try (InputStream stream = Files.newInputStream(path)) {
            while ((bytesRead = stream.read(bytes)) >= 0) {
                result = hash(bytes, bytesRead, result);
            }
        } catch (IOException e) {
            System.err.println("An exception has occurred when reading the contents of the following file: " + fileName + " " + e.getMessage());
            result = ERROR_ZERO;
        }

        return result;
    }
}
