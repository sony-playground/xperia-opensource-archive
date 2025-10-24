package com.sony.fl.db;

import static org.junit.Assert.assertEquals;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;

import com.sony.fl.Configuration;
import com.sony.fl.exception.FLException;

import org.apache.commons.io.file.PathUtils;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class TestDBForPredictManager {
    public Path root = Paths.get("src/test/resources/PredictManagerRoot");
    public DBForPredictManager db;

    @Before
    public void setUpUsingSQLite() 
            throws IOException, InstantiationException, IllegalAccessException, 
            ClassNotFoundException, FLException {
        Files.createDirectories(root);
        db = new DBForPredictManager((DBFactory)Class.forName(
                Configuration.DB_FACTORY_FQCN).newInstance() ,root);
    }

    @After
    public void cleaning() throws IOException {
        PathUtils.deleteDirectory(root);
    }

    @Test
    public void testDBForTrainManager() {
        String appID = "app_1";
        String oldPath = "old/path";
        byte[] oldModel = "oldModel".getBytes();
        String newPath = "new/path";
        byte[] newModel = "newModel".getBytes();
        assertEquals(true, db.searchForBackUpPathFromDB(appID) == null);
        assertEquals(true, db.searchForModelInfoFromDB(appID) == null);
        assertEquals(0, db.updateAppInfoOnDB(appID, oldPath, oldModel));
        assertEquals(true, db.searchForBackUpPathFromDB(appID).equals(oldPath));
        assertEquals(true, Arrays.equals(db.searchForModelInfoFromDB(appID), oldModel));
        assertEquals(0, db.updateAppInfoOnDB(appID, newPath, newModel));
        assertEquals(true, db.searchForBackUpPathFromDB(appID).equals(newPath));
        assertEquals(true, Arrays.equals(db.searchForModelInfoFromDB(appID), newModel));
        assertEquals(0, db.deleteBackUpFromDB(appID));
        assertEquals(true, db.searchForBackUpPathFromDB(appID) == null);
        assertEquals(true, db.searchForModelInfoFromDB(appID) == null);
    }

    @Test
    public void testCreateDBWithWrongPath() 
            throws InstantiationException, IllegalAccessException, ClassNotFoundException {
        Path badPath = Paths.get("bad/path");
        boolean flag = true;
        try {
            db = new DBForPredictManager((DBFactory)Class.forName(
                    Configuration.DB_FACTORY_FQCN).newInstance() , badPath);
        } catch (FLException e) {
            flag = false;
        }
        if (flag) {
            assertEquals(0, 1);
        }
    }

}