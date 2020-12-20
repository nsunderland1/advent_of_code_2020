open Core;;
let (=) = Poly.(=)
let (<>) = Poly.(<>)

let parse_line line =
  let open Angstrom in
  let parse parser = Result.ok_or_failwith (parse_string ~consume:All parser line) in
  let integer =
    take_while1 (function '0' .. '9' -> true | _ -> false) >>| int_of_string
  in
  let id = string "Tile" *> char ' ' *> integer <* char ':' in
  let row = many1 (choice [char '#'; char '.']) in
  let tile = sep_by1 (char '\n') row in
  let data = (fun num tiledata -> (num, tiledata)) <$> id <* char '\n' <*> tile in
  parse data

let print_integer some_int =
  print_endline "";
  Out_channel.output_string stdout (string_of_int some_int)

type side = Top | Bot | Left | Right

let sides tile = [
  Top, List.hd_exn tile;
  Bot, List.last_exn tile;
  Left, List.map ~f:(fun row -> List.hd_exn row) tile;
  Right, List.map ~f:(fun row -> List.last_exn row) tile;
]

let can_join tile1 tile2 =
  let sides1, sides2 = Tuple2.map ~f:sides (tile1, tile2) in
  List.find_map ~f:(fun (d1, side1) ->
    List.find_map ~f:(fun (d2, side2) ->
      if side1 = side2 then
        Some (d1, d2, false)
      else if (List.rev side1) = side2 then
        Some (d1, d2, true)
      else
        None
    ) sides2
  ) sides1

let get_joins tiles id1 tile1 =
  Map.filter_mapi ~f:(fun ~key:id2 ~data:tile2 ->
    if id1 = id2 then
      None
    else
      Option.map
        ~f:(fun (side1, side2, rev) -> (id2, side1, side2, rev))
        (can_join tile1 tile2))
  tiles
  |> Map.to_alist |> List.map ~f:(fun (_, rest) -> rest) 

let find_corners tiles =
  Map.filter_mapi ~f:(fun ~key:id1 ~data:tile1 ->
    let joins = get_joins tiles id1 tile1 in
    if List.length joins = 2 then Some joins else None
  ) tiles |> Map.to_alist
let tile_size = 10
let grid_size = 12

let flipx = List.map ~f:List.rev
let flipy = List.rev
let rec rotate_aux tile =
  if List.length (List.hd_exn tile) = 0 then
    []
  else
    (List.map ~f:List.hd_exn tile |> List.rev)::(rotate_aux (List.map ~f:List.tl_exn tile))

let rotate tile =
  (* List.iter ~f:(fun row -> List.iter ~f:(fun c -> Out_channel.output_char stdout c) row; print_endline "") tile;
  print_endline ""; *)
  rotate_aux tile
let rec build_toprow leftid lefttile tiles =
  let joins = get_joins tiles leftid lefttile in
  let maybe_next = List.find_map ~f:(fun (id, side1, side2, rev) -> if side1=Right then Some (id, side2, rev) else None) joins in
  match maybe_next with
  | None -> (tiles, [])
  | Some (id, side, rev) -> (
      let nexttile = Map.find_exn tiles id in
      let nexttile = match (side, rev) with
      | Left, false -> nexttile
      | Left, true -> flipy nexttile
      | Right, false -> flipx nexttile
      | Right, true -> rotate (rotate nexttile)
      | Top, false -> rotate (rotate (rotate (flipx nexttile)))
      | Top, true -> rotate (rotate (rotate nexttile))
      | Bot, false -> rotate nexttile
      | Bot, true -> rotate (flipx nexttile)
      in
      let newtiles = Map.remove tiles id in
      let (resttiles, rest) = build_toprow id nexttile newtiles in
      (resttiles, nexttile::rest)
  )

let build tiles =
  let rec build_aux startid tiles =
    let starttile = Map.find_exn tiles startid in
    let startjoins = get_joins tiles startid starttile in
    let sides = List.map ~f:(fun (_, side, _, _) -> side) startjoins in
    let starttile = if List.exists ~f:(fun side -> side = Top) sides then flipy starttile else starttile in
    let starttile = if List.exists ~f:(fun side -> side = Left) sides then flipx starttile else starttile in
    let tiles = Map.remove tiles startid in
    let (newtiles, toprow) = build_toprow startid starttile tiles in
    let next =
      get_joins newtiles startid starttile
      |> List.find_map ~f:(fun (id2, side, side2, rev) -> if side = Bot then Some (id2, side2, rev) else None)
    in
    match next with
    | None -> [starttile::toprow]
    | Some (nextid, side, rev) ->
        let nexttile = Map.find_exn newtiles nextid in  
        let nexttile = match side, rev with
        | Top, false -> nexttile
        | Top, true -> flipx nexttile
        | Bot, false -> flipy nexttile
        | Bot, true -> rotate (rotate nexttile)
        | Left, false -> rotate (flipy nexttile)
        | Left, true -> rotate nexttile
        | Right, false -> rotate (rotate (rotate nexttile))
        | Right, true -> (rotate (rotate (rotate (flipy nexttile))))
        in
        let newtiles = Map.set newtiles ~key:nextid ~data:nexttile in
        (starttile::toprow)::(build_aux nextid newtiles)
  in
  let corners = find_corners tiles in
  let (startid, _) = List.hd_exn corners in
  build_aux startid tiles

module IntMap = Map.Make(Int)

let fout = Out_channel.create "output"

let drop_border lst = List.drop_last_exn (List.drop lst 1)

let _ =
  (* let tiles = In_channel.read_all "input" |> Re2.split (Re2.create_exn "\n\n") in
  let tiles = List.drop_last_exn tiles in
  let data = List.map ~f:parse_line tiles in
  let tilemap = List.fold ~init:IntMap.empty ~f:(fun map (id, tile) -> IntMap.add_exn map ~key:id ~data:tile) data in
  let res = List.fold ~f:(fun acc (id, _) -> acc*id) ~init:1 (find_corners tilemap) in
  let grid = build tilemap in
  let cleaned = List.map ~f:(fun row ->
    List.map ~f:(fun tile ->
      List.map ~f:drop_border (drop_border tile)
    ) row
  ) grid
  in
  List.iter ~f:(fun row ->
    let lines = List.init 8 ~f:(fun i -> List.map ~f:(fun tile -> List.nth_exn tile i) row) in
    List.iter ~f:(fun line ->
      List.iter ~f:(fun part ->
        List.iter ~f:(fun c ->
          Out_channel.output_char fout c;
        ) part;
        Out_channel.output_char fout ' '
      ) line;
      Out_channel.output_char fout '\n';
    ) lines;
    Out_channel.output_char fout '\n';
  ) cleaned;
  print_integer (List.length grid);
  print_integer res *)
  (* At this point I joined the grids together using my text editor *)
  let fullgrid = In_channel.read_lines "full_grid_unbordered" |> List.map ~f:String.to_list in
  let versions = List.map ~f:(fun grid ->
    List.map ~f:String.of_char_list grid |> String.concat ~sep:"\n"
  ) [
    fullgrid;
    fullgrid |> rotate;
    fullgrid |> rotate |> rotate;
    fullgrid |> rotate |> rotate |> rotate;
    flipx fullgrid;
    flipx fullgrid |> rotate;
    flipx fullgrid |> rotate |> rotate;
    flipx fullgrid |> rotate |> rotate |> rotate;
  ]
  in
  let regex1 = Re2.create_exn "#[.#][.#][.#][.#]##[.#][.#][.#][.#]##[.#][.#][.#][.#]###" in
  let regex2 = Re2.create_exn "[.#]#[.#][.#]#[.#][.#]#[.#][.#]#[.#][.#]#[.#][.#]#[.#][.#][.#]" in
  let valid = List.filter ~f:(fun version -> Re2.matches regex1 version && Re2.matches regex2 version) versions in
  (* List.iteri ~f:(fun i gridtry ->
    let out = Out_channel.create (Printf.sprintf "try%d" i) in
    Out_channel.output_string out gridtry
  ) valid; *)
  (* Solved by inspection *)
  let correct = List.hd_exn valid in
  (* Numbers determined by inspection *)
  print_integer ((String.count ~f:(fun c -> c = '#') correct) - 15*34)

