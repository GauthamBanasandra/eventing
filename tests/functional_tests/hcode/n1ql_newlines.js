function OnUpdate(doc, meta) {
    var docId = meta.id;

    // This comment is supposed to cause problem with N1QL compilation
    INSERT
        INTO
                (KEY, VALUE)