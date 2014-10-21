import java.sql.Timestamp;
import java.util.Date;

class database
{
//================================Fields================================
//================================Constructors================================
  public database() 
  {
    
  }
//================================Methods================================
  public int getCount(int group)
  {
    return 0;
  }
  
  public void addTPoints(ArrayList<tPoint> _tPoints, int group)
  {
    String temp[] = new String[_tPoints.size()];
   for (int i=0; i<_tPoints.size();i++)
   {
     temp[i]=_tPoints.get(i).toString();
   }
   java.util.Date date= new java.util.Date();
   long timestamp = date.getTime();
   saveStrings(nf(group,1) + "\\" + Long.toString(timestamp) + ".txt", temp);
  }
  
  public ArrayList<tPoint> getTPoints(int number, int group)
  {
     return null;
  }
  
  public void clearDatabase(int group)
  {
  }

  public void clearDatabase()
  {
    for(int i=1; i<=4; i++)
    {
      clearDatabase(i);
    }
  }
}


