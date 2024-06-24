import java.io.*;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class Solution {
    private static final char LINE_END = '\n';
    private final InputStream input;
    private final OutputStream output;
    private final CommandFactory commandFactory;
    private final CommandExecutor commandExecutor;
    private final ByteArrayOutputStream outputBuffer;
    private char[] string;

    public static void main(String[] args) {
        Solution solutionHammingDistance = new Solution(System.in, System.out);
        try {
            solutionHammingDistance.process();
        } catch (IOException e) {
            throw new IllegalArgumentException(e);
        }
    }

    public Solution(InputStream input, OutputStream output) {
        this.input = input;
        this.output = output;
        commandFactory = new CommandFactory();
        commandExecutor = new CommandExecutor();
        outputBuffer = new ByteArrayOutputStream();
    }

    public void process() throws IOException  {
        readInt();
        string = readLine().toCharArray();
        readInt();
        Queue<Command> commands = processCommands();

        while (!commands.isEmpty()) {
            commandExecutor.execute(commands.remove());
        }

        output.write(outputBuffer.toByteArray());
    }

    private Queue<Command> processCommands() {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(input));
        return bufferedReader.lines().map(commandFactory::create).collect(Collectors.toCollection(LinkedList::new));
    }

    private int readInt() throws IOException {
        String line = readLine();
        return Integer.valueOf(line);
    }

    private String readLine() throws IOException {
        StringBuilder line = new StringBuilder();
        int readByte = input.read();
        while (readByte != -1) {
            line.append((char) readByte);
            readByte = input.read();
            if (readByte == LINE_END) {
                return line.toString();
            }
        }
        return line.toString();
    }

    private class CommandFactory {
        private Command create(String commandString) {
            char commandType = commandString.charAt(0);
            String[] commandArguments = commandString.split(" ");
            Command commandToReturn;
            switch (commandType) {
                case 'H': {
                    HammingDistance command = new HammingDistance();
                    command.firstStart = createIndex(commandArguments[1]);
                    command.secondStart = createIndex(commandArguments[2]);
                    command.length = Integer.valueOf(commandArguments[3]);
                    commandToReturn = command;
                    break;
                }
                case 'C': {
                    Change command = new Change();
                    command.left = createIndex(commandArguments[1]);
                    command.right = createIndex(commandArguments[2]);
                    command.ch = commandArguments[3].charAt(0);
                    commandToReturn = command;
                    break;
                }
                case 'S': {
                    Swap command = new Swap();
                    command.left1 = createIndex(commandArguments[1]);
                    command.right1 = createIndex(commandArguments[2]);
                    command.left2 = createIndex(commandArguments[3]);
                    command.right2 = createIndex(commandArguments[4]);
                    commandToReturn = command;
                    break;
                }
                case 'R': {
                    Reverse command = new Reverse();
                    command.left = createIndex(commandArguments[1]);
                    command.right = createIndex(commandArguments[2]);
                    commandToReturn = command;
                    break;
                }
                case 'W': {
                    Wipe command = new Wipe();
                    command.left = createIndex(commandArguments[1]);
                    command.right = createIndex(commandArguments[2]);
                    commandToReturn = command;
                    break;
                }
                default:
                    throw new IllegalArgumentException("Cannot found command! String: " + commandString);
            }
            return commandToReturn;
        }

        private int createIndex(String index) {
            return Integer.valueOf(index) - 1;
        }
    }

    private class CommandExecutor {
        private void execute(Command command) throws IOException {
            if (command instanceof MutingCommand) {
                string = command.execute(string);
            } else if (command instanceof OutputCommand) {
                String result = new String(command.execute(string));
                result += LINE_END;
                outputBuffer.write(result.getBytes());
            }
        }
    }

    private interface MutingCommand extends Command {
    }

    private interface OutputCommand extends Command {
    }

    private interface Command {
        char[] execute(char[] string);
    }

    private class HammingDistance implements OutputCommand {
        int firstStart;
        int secondStart;
        int length;

        @Override
        public char[] execute(char[] string) {
            long sum = 0L;
            for (int i = 0; i < length; i++) {
                if (string[firstStart + i] != string[secondStart + i]) {
                    sum++;
                }
            }
            return Long.toString(sum).toCharArray();
        }
    }

    private class Change implements MutingCommand {
        int left;
        int right;
        char ch;


        @Override
        public char[] execute(char[] string) {
            for (int i = left; i <= right; i++) {
                string[i] = ch;
            }
            return string;
        }
    }

    private class Swap implements MutingCommand {
        int left1;
        int right1;
        int left2;
        int right2;

        @Override
        public char[] execute(char[] string) {
            char[] newString = Arrays.copyOf(string, string.length);
            int i = left1;
            int rightSize = right2 - left2 + 1;
            int leftSize = right1 - left1 + 1;
            int restSize = left2 - right1 - 1;
            for (int j = 0; i < left1 + rightSize; i++, j++) {
                newString[i] = string[left2 + j];
            }
            for (int j = 0; i < left1 + rightSize + restSize; i++, j++) {
                newString[i] = string[left1 + leftSize + j];
            }
            for (int j = 0; i < left1 + rightSize + restSize + leftSize; i++, j++) {
                newString[i] = string[left1 + j];
            }
            return newString;

        }
    }

    private class Reverse implements MutingCommand {
        int left;
        int right;

        @Override
        public char[] execute(char[] string) {
            char[] chars = Arrays.copyOf(string, string.length);
            for (int i = 0; i <= right - left; i++) {
                chars[right - i] = string[left + i];
            }
            return chars;
        }
    }

    private class Wipe implements OutputCommand {
        private int left;
        private int right;

        @Override
        public char[] execute(char[] string) {
            return new String(string).substring(left, right + 1).toCharArray();
        }
    }

}
