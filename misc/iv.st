group taste;

interface_view(arrsThreadNames, arrsPassiveNames, arrsConnections) ::= <<
# TASTE Interface View
# Save this output to file.dot and run "neato file.dot -Tpng -o out.png"

digraph interfaceview {
    overlap=scale;
    splines=ortho;
    sep=0.2;
<arrsThreadNames: {each|    <each> [shape=parallelogram, style=filled, fontsize=24, label="<each>"];}; separator="\n">
<arrsPassiveNames: {each|    <each> [shape=box, fillcolor=cyan, style="filled, rounded", fontsize=20, label="<each>"];}; separator="\n">

<arrsConnections; separator="\n">
}
>>

connection(sFrom, sTo, arrsMessages) ::= <<
    <sFrom> -> <sTo> [fontsize=14, color=blue, taillabel="[<arrsMessages; separator=",\n">]"];
>>
