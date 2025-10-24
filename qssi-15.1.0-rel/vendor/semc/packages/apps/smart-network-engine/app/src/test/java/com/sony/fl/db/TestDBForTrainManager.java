package com.sony.fl.db;

import static org.junit.Assert.assertEquals;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import com.sony.fl.Configuration;
import com.sony.fl.exception.FLException;

import org.apache.commons.io.file.PathUtils;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class TestDBForTrainManager {
    public Path root = Paths.get("src/test/resources/TrainManagerRoot");
    public DBForTrainManager db;

    @Before
    public void setUpDB() 
            throws IOException, InstantiationException, IllegalAccessException, 
            ClassNotFoundException, FLException {
        Files.createDirectories(root);
        db = new DBForTrainManager((DBFactory)Class.forName(
                Configuration.DB_FACTORY_FQCN).newInstance() ,root);
    }

    @After
    public void cleaning() throws IOException {
        PathUtils.deleteDirectory(root);
    }

    @Test
    public void testDBForTrainManager() {
        String FLID = "fl_1";
        String oldPath = "old/path";
        String newPath = "new/path";
        assertEquals(true, db.searchForBackUpPathFromDB(FLID) == null);
        assertEquals(0, db.updateBackUpPathOnDB(FLID, oldPath));
        assertEquals(true, db.searchForBackUpPathFromDB(FLID).equals(oldPath));
        assertEquals(0, db.updateBackUpPathOnDB(FLID, newPath));
        assertEquals(true, db.searchForBackUpPathFromDB(FLID).equals(newPath));
        assertEquals(0, db.deleteBackUpFromDB(FLID));
        assertEquals(true, db.searchForBackUpPathFromDB(FLID) == null);
    }

    @Test
    public void testCreateDBWithWrongPath() 
            throws InstantiationException, IllegalAccessException, ClassNotFoundException {
        Path badPath = Paths.get("bad/path");
        boolean flag = true;
        try {
            db = new DBForTrainManager((DBFactory)Class.forName(
                    Configuration.DB_FACTORY_FQCN).newInstance() , badPath);
        } catch (FLException e) {
            flag = false;
        }
        if (flag) {
            assertEquals(0, 1);
        }
    }

}