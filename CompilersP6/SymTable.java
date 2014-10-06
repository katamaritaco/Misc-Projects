import java.util.*;

public class SymTable {
    private List<HashMap<String, Sym>> list;
    
    public SymTable() {
        list = new LinkedList<HashMap<String, Sym>>();
        list.add(new HashMap<String, Sym>());
    }
    
    public void addDecl(String name, Sym sym) 
    throws DuplicateSymException, EmptySymTableException {
        if (name == null || sym == null)
            throw new NullPointerException();
        
        if (list.isEmpty())
            throw new EmptySymTableException();
        
        HashMap<String, Sym> symTab = list.get(0);
        if (symTab.containsKey(name))
            throw new DuplicateSymException();
        
        symTab.put(name, sym);
    }
    
    public void addScope() {
        list.add(0, new HashMap<String, Sym>());
    }
    
    public Sym lookupLocal(String name) {
        if (list.isEmpty())
            return null;
        
        HashMap<String, Sym> symTab = list.get(0); 
        return symTab.get(name);
    }
    
    public Sym lookupGlobal(String name) {
        if (list.isEmpty())
            return null;
        
        for (HashMap<String, Sym> symTab : list) {
            Sym sym = symTab.get(name);
            if (sym != null)
                return sym;
        }
        return null;
    }

    //XXX added by Leo
    /*public Iterator< Hashmap<String, Sym> > localIterator()
    {
        return list.get(0).iterator();
    }*/

    public void setGlobals()
    {
        //get the last hashmap in the list
        //it should be the global hashmap
        HashMap <String, Sym> globalMap = ((LinkedList<HashMap<String, Sym>>)list).getLast();//size shouldn't be zero :3

        for ( Map.Entry<String, Sym> entry : globalMap.entrySet())
        {
            entry.getValue().setIsGlobal();
        }

    }
    
    public void removeScope() throws EmptySymTableException {
        if (list.isEmpty())
            throw new EmptySymTableException();
        list.remove(0);
    }
    
    public void print() {
        System.out.print("\nSym Table\n");
        for (HashMap<String, Sym> symTab : list) {
            System.out.println(symTab.toString());
        }
        System.out.println();
    }
}
