// GraphImplementation.java - supplied code for graph assignment
// Author: ?????
// Date:   ?????
// Class:  CS165
// Email:  ?????

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

public class GraphImplementation extends GraphAbstract {

    // Main entry point
    public static void main(String[] args) {

        if (args.length != 2) {
            System.err.println("usage: java GraphImplementation <distanceFile> <graphFile>");
            System.exit(-1);
        }

        // Instantiate code
        GraphImplementation impl = new GraphImplementation();

        // Read distances chart
        System.out.println("Reading Chart: " + args[0]);
        impl.readGraph(args[0]);
        System.out.println();

        // Write distances graph
        System.out.println("Writing Graph: " + args[1]);
        impl.writeGraph(args[1]);
        System.out.println();

        // Print depth first search
        System.out.println("Depth First Search:");
        impl.depthFirst("Fort Collins");
        System.out.println();

        // Print breadth first search
        System.out.println("Breadth First Search:");
        impl.breadthFirst("Fort Collins");
        System.out.println();

        /*
        // EXTRA CREDIT: Print all shortest paths
        for (int from = 0; from < cities.size(); from++) {
            for (int to = 0; to < cities.size(); to++)
                if (from != to) {
                    String fromCity = cities.get(from).name;
                    String toCity = cities.get(to).name;
                    System.out.print("Shortest Path: ");
                    impl.shortestPath(fromCity, toCity);
                }
        }
        */
    }

    // Reads mileage chart from CSV file
    public void readGraph(String filename) {
        // YOUR CODE HERE
        ArrayList<String> contents = readFile(filename);
//        System.out.println("line one: " + contents.get(0).toString());
//        System.out.println("line two: " + contents.get(1).toString());
        String[] city = contents.get(0).split(",");
        for(int i = 1; i < city.length; i++) {
        	cities.add(new GraphNode(city[i]));
        }
        
        for(int i = 1; i < contents.size(); i++) {
    		String[] line = contents.get(i).split(",");
        	for(int j = 1; j < line.length; j++) {
        		if(!line[j].isEmpty()) {
        			mileages.add(new GraphEdge(i-1, j-1, Integer.parseInt(line[j])));
        		}
        	}
        }
        mileages.sort(null);
        for(int i = 0; i < mileages.size(); i++) {   	
       		cities.get(mileages.get(i).fromIndex).edges.add(mileages.get(i));
       		cities.get(mileages.get(i).toIndex).edges.add(new GraphEdge(mileages.get(i).toIndex, mileages.get(i).fromIndex, mileages.get(i).mileage));
        }
        mileages.sort(null);
    }

    public void writeGraph(String filename) {

        ArrayList<String> output = new ArrayList<>();
        output.add("digraph BST {");
        output.add("    ratio = 1.0;");
        output.add("    node [style=filled]");
        output.add("    node [fillcolor=darkslateblue]");
        output.add("    node [fixedsize=true]");
        output.add("    node [shape=oval]");
        output.add("    node [width=6]");
        output.add("    node [height=4]");
        output.add("    node [fontname=Arial]");
        output.add("    node [fontsize=60]");
        output.add("    node [fontcolor=white]");
        output.add("    edge [dir=none]");
        output.add("    edge [penwidth=24]");
        output.add("    edge [fontname=Arial]");
        output.add("    edge [fontsize=110]");
        
        // YOUR CODE HERE
        // Write distances graph
        //formating for cities and edges
        //" Node%d [label=\"%s\"];" FromIndex, name
        for(int i = 0; i < cities.size(); i++) {
        output.add("    Node" +i+ "[label=\""+cities.get(i).name+"\"];");
        }
        //" Node%d -> Node%d [label=\"%d\" color=\"%s\"]" FromIndex, toIndex, mileage, color
        for(int i = 0; i < mileages.size(); i++) {
        	if(mileages.get(i).mileage > 0 && mileages.get(i).mileage <= 100) {
                output.add("    Node"+mileages.get(i).fromIndex+" -> Node"+mileages.get(i).toIndex+" [label=\""+mileages.get(i).mileage+"\" color=\"green\"]");
        	}
        	if(mileages.get(i).mileage > 100 && mileages.get(i).mileage <= 200) {
                output.add("    Node"+mileages.get(i).fromIndex+" -> Node"+mileages.get(i).toIndex+" [label=\""+mileages.get(i).mileage+"\" color=\"blue\"]");
        	}
        	if(mileages.get(i).mileage > 200 && mileages.get(i).mileage <= 300) {
                output.add("    Node"+mileages.get(i).fromIndex+" -> Node"+mileages.get(i).toIndex+" [label=\""+mileages.get(i).mileage+"\" color=\"magenta\"]");
        	}
        	if(mileages.get(i).mileage > 300) {
                output.add("    Node"+mileages.get(i).fromIndex+" -> Node"+mileages.get(i).toIndex+" [label=\""+mileages.get(i).mileage+"\" color=\"red\"]");
        	}
        }
        output.add("}");
        writeFile(filename, output);
    }



    public void depthFirst(String startCity) {
        // YOUR CODE HERE
    	for(int i = 0; i < cities.size(); i++) {
    		if(cities.get(i).name.equals(startCity)) {
    			ArrayList<Integer> visited = new ArrayList<Integer>();
    			depthFirst(i, visited);
    		}
    	}
    }

    // Recursive helper method
    public void depthFirst(int index, ArrayList<Integer> visited) {
        // YOUR CODE HERE
//    	if(!visited.contains(index)) {
//    		visited.add(index);
//    		System.out.println("Visited " + cities.get(index).name);
//    		int lowest = 1000000;
//    		for(int i = 0; i < cities.get(index).edges.size(); i++) {
//    				
//    				index = cities.get(index).edges.get(i).toIndex;
//    				depthFirst(index, visited);    			
//    		}
//    	}
    	visited.add(index);
    	System.out.println("Visited: " + cities.get(index).name);
		for(int i = 0; i < cities.get(index).edges.size(); i++) {
			int city = cities.get(index).edges.get(i).toIndex;
			if(!visited.contains(city)) {
				depthFirst(city, visited);
			}
		
		}
    }
    

    public void breadthFirst(String startCity) {
        // YOUR CODE HERE
		ArrayList<String> visited = new ArrayList<String>();
    	Queue<Integer> queue = new LinkedList<Integer>();
    	for(int i = 0; i < cities.size(); i++) {
    		if(cities.get(i).name.equals(startCity)) {
    			queue.add(i);
    			visited.add(startCity);
    		}
    	}
    	while(!queue.isEmpty()) {
    		int next = queue.poll();
    		System.out.println("Visited: " + cities.get(next).name);
    		for(int i = 0; i < cities.get(next).edges.size(); i++) {
    			String city = cities.get(cities.get(next).edges.get(i).toIndex).name;
        		if(!visited.contains(city)) {
        			queue.add(cities.get(next).edges.get(i).toIndex);
        			visited.add(city);
        		}
    		}
    	}
    }


    public void shortestPath(String fromCity, String toCity) {
        // YOUR CODE HERE
    	
    }

    // Helper functions

    /**
     * Reads the contents of file to {@code ArrayList}
     * @param filename the file to read from
     * @return an ArrayList of the contents
     */
    static ArrayList<String> readFile(String filename) {
        ArrayList<String> contents = new ArrayList<>();
        try(Scanner reader = new Scanner(new File(filename))) {
            while (reader.hasNextLine()) {
                String line = reader.nextLine().trim();
                if (!line.isEmpty())
                    contents.add(line);
            }
        } catch (IOException e) {
            System.err.println("Cannot read chart: " + filename);
        }
        return contents;
    }

    /**
     * Write contents of {@code ArrayList} to file
     * @param filename the name of the file to write to
     * @param contents an ArrayList of contents to write
     */
    static void writeFile(String filename, ArrayList<String> contents) {
        try(PrintWriter writer = new PrintWriter(filename)) {
            for (String line : contents)
                writer.println(line);
        } catch (IOException e) {
            System.err.println("Cannot write graph: " + filename);
        }
    }
}
