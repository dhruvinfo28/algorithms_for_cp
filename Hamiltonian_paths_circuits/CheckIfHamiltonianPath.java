//Definition: A hamiltonian path is a path in a graph that covers each vertex exactly once
//Approach: A hamiltonian path is nothing but a permutation of all the vertices (v1,v2,v3....vn)
//such that there is an edge between vi and vi+1
//So we can go through all permutations and see if it is a path or not

//time complexity: O(n*n!) , n! permutations and O(n) to check if that permutation is a path

import java.util.*;

public class CheckIfHamiltonianPath{
    private static Scanner scanner = new Scanner(System.in);
    public static void main(String[] args){
        int n = scanner.nextInt();
        int m = scanner.nextInt();

        //Since in the approach given above we are going to check if there is an edge between
        //two vertices , an adjacency matrix will best serve the purpose as it tells that in
        //O(1)

        int adj[][] = new int[n][n];
        int a,b;
        for(int i=0;i<m;i++){
            a = scanner.nextInt();
            b = scanner.nextInt();
            adj[a][b] = 1;
            adj[b][a] = 1;
        }

        int[] permutation = new int[n];
        for(int i=0;i<n;i++){
            permutation[i] = i;
        }

        System.out.println(generateP(permutation,n,0,adj));
    }

    public static boolean generateP(int[] permutation, int n, int level, int[][] adj){
        if(level==n){
            if(checkIfPath(permutation,adj)){
                return true;
            }
        }
        for(int i=level;i<n;i++){
            swap(permutation,level,i);
            if(generateP(permutation,n,level+1,adj)){ return true;}
            swap(permutation,level,i);
        }
        return false;
    }

    public static boolean checkIfPath(int[] permutation, int[][] adj){
        for(int i=0;i<permutation.length-1; i++){
            if(adj[i][i+1]!=1){
                return false;
            }
        }
        return true;
    }

    public static final void swap(int[] arr, int i, int j){
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}