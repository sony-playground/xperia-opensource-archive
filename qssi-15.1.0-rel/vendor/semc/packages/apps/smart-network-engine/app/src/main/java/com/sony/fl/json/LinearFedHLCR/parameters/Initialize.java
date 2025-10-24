package com.sony.fl.json.LinearFedHLCR.parameters;

import java.util.ArrayList;
import java.util.List;

import com.sony.fl.json.AbstractMessage;

/*
 * {
 *   "method": "Initialize",
 *   "parameters": {
 *     "server": {
 *       "globalWeight": "aaa",
 *       "linearModels": [ "bbb", "ccc" ]
 *     },
 *     "internal": {
 *       "clusterMap": "ddd"
 *     }
 *   }
 * }
 */
public class Initialize extends AbstractMessage {

    public Initialize() {}

    public Parameters parameters = new Parameters();

    public static class Parameters {
        public final Server server = new Server();
        public final Internal internal = new Internal();

        public static class Server {
            public String globalWeight;
            public final List<String> linearModels = new ArrayList<>();
        }

        public static class Internal {
            public String clusterMap;
        }
    }

    protected String myName() {
        return "Initialize";
    }

    public static Initialize newInstance() {
        return (Initialize)AbstractMessage.newInstance(Initialize.class);
    }
}
