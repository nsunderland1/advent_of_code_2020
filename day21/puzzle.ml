open Core;;
let (=) = Poly.(=)
let (<>) = Poly.(<>)

let ignore_empty_lines = true

let parse_line line =
  let open Angstrom in
  let parse parser = Result.ok_or_failwith (parse_string ~consume:All parser line) in
  let lowercase =
    take_while1 (function 'a' .. 'z' -> true | _ -> false)
  in
  let ingredients = sep_by1 (char ' ') lowercase in
  let allergens = string "(contains " *> (sep_by1 (string ", ") lowercase) <* char ')' in
  let food = (fun ings alls -> (ings, alls)) <$> ingredients <* char ' ' <*> allergens in
  parse food

let print_integer some_int =
  print_endline "";
  Out_channel.output_string stdout (string_of_int some_int)

module StringSet = Set.Make(String)
module StringMap = Map.Make(String)
let _ =
  let lines = In_channel.read_lines "cleaned" in
  let lines = if ignore_empty_lines then List.filter ~f:(fun line -> not (phys_equal line "")) lines else lines in
  let data = List.map ~f:parse_line lines in
  let ingredients = List.fold ~f:(fun acc (ings, _) ->
    List.fold ~f:(fun acc ing -> StringSet.add acc ing) ~init:acc ings
  ) ~init:StringSet.empty data
  in 
  let allergens = List.fold ~f:(fun acc (_, ings) ->
      List.fold ~f:(fun acc ing -> StringSet.add acc ing) ~init:acc ings
    ) ~init:StringSet.empty data
  in
  (* let non_allergen = Set.filter ~f:(fun ing ->
      let does_not_contain =
        data
        |> List.filter ~f:(fun (ings, _) -> not (List.mem ~equal:String.equal ings ing))
        |> List.map ~f:(fun (_, alls) -> alls)
        |> List.concat
        |> List.dedup_and_sort ~compare:String.compare
      in
      List.length does_not_contain = Set.length allergens
    ) ingredients
  in *)
  (* let res = Set.fold ~f:(fun acc ing ->
    acc + List.count ~f:(fun (ings, _) -> List.mem ~equal:String.equal ings ing) data
  ) ~init:0 non_allergen *)
  (* let cleaned_data = List.map ~f:(fun (ings, alls) ->
    (List.filter ~f:(fun ing -> not (StringSet.mem non_allergen ing)) ings, alls)
  ) data
  in *)
  (* let fout = Out_channel.create "cleaned" in
  List.iter ~f:(fun (ings, alls) ->
      Out_channel.output_string fout (String.concat ~sep:" " ings);
      Out_channel.output_string fout " (contains ";
      Out_channel.output_string fout (String.concat ~sep:", " alls);
      Out_channel.output_string fout ")\n"
    ) cleaned_data *)
  let allergen_map = Set.fold ~f:(fun acc all ->
      Map.add_exn acc ~key:all ~data:ingredients
    ) ~init:StringMap.empty allergens
  in
  let possible = List.fold ~f:(fun acc (ings, alls) ->
      List.fold ~f:(fun acc all ->
          StringSet.fold ~f:(fun acc ing ->
            if List.mem ~equal:String.equal ings ing then
              acc
            else
              let possible_for = Map.find_exn acc all in
              Map.set acc ~key:all ~data:(Set.remove possible_for ing)
          ) ~init:acc ingredients
        ) ~init:acc alls
    ) ~init:allergen_map data
  in
  StringMap.iteri ~f:(fun ~key ~data ->
      Printf.printf "%s: %s\n" key (String.concat ~sep:", " (StringSet.to_list data))
    ) possible
  